#include "main.h"
#include "Constantes.h"
#include "draw_utils.h"

cTray *ctray;
HMENU popup;

using namespace std;

fstream *flog;

void destroyApp()
{
	if(flog)
	{
		flog->close();
		delete flog;
	}
}

int CALLBACK_STATUS(int error,const char *const pStrStatus,int progress)
{
	if(flog)
	{
		TCHAR buffer[255];
		ZeroMemory(buffer,sizeof(buffer));
		sprintf(buffer,"----------\nError: %d \nStatus: %s\n----------\n",error,pStrStatus);
		flog->write(buffer,lstrlen(buffer));
	}
	if(error!=STATUS_OK)
	{
		MessageBox(0,pStrStatus,"Error!",0);
		destroyApp();
		ExitProcess(0);
	}
	return 0;
}


LRESULT CALLBACK MainWndProc(

    HWND hwnd,	// handle of window
    UINT uMsg,	// message identifier
    WPARAM wParam,	// first message parameter
    LPARAM lParam 	// second message parameter
   )
{
	switch(uMsg)
	{
	case WM_CREATE:
		
		cMonitor=new CHWMonitor(CALLBACK_STATUS,CurDir);
		if(!cMonitor)
			ExitProcess(0);
		for(int i=0;i<10;i++)
		{
			Temperatures[i].max=-1000;
			Temperatures[i].min=1000;

			Voltages[i].min=36;
			Voltages[i].max=-36;
		}
		InitTabs(hinst,hwnd);
		///init tray
		//Add to systray
		ctray=new cTray(hwnd,IDTRAY1);
		ctray->setIcon(CreateSmallIcon(hwnd,"0"));
		ctray->setCallbackMessage(WM_TRAY);
		ctray->show();
		///
		popup=CreatePopupMenu();
		AppendMenu(popup, MF_STRING | MF_ENABLED ,ID_MENU_RESTORE,"Show Setting");
		AppendMenu(popup, MF_SEPARATOR | MF_DISABLED ,ID_MENU_EXIT,NULL);
		AppendMenu(popup, MF_STRING | MF_ENABLED ,ID_MENU_EXIT,"Exit");
		///
		SetTimer(hwnd,IDTIMER1,500,NULL);

		break;
	case WM_SHOWWINDOW:
		if((BOOL)wParam)
		{
			ModifyMenu(popup,0, MF_BYPOSITION | MF_STRING | MF_ENABLED ,ID_MENU_HIDE,"Hide form");
		}
		break;
	case WM_CLOSE:
		ModifyMenu(popup,0, MF_BYPOSITION | MF_STRING | MF_ENABLED ,ID_MENU_RESTORE,"Show form");
		ShowWindow(hwnd,SW_HIDE);
		return 0;
	case WM_DESTROY:
		DestroyMenu(popup);
		KillTimer(hwnd,IDTIMER1);
		FreeTabs();
		
		if(cMonitor)
		{
			cMonitor->setBlock(FALSE);
			delete cMonitor;
		}
		break;
	case WM_TIMER:
		char buff[128];
		SENSOR sensor;
		//============Temperatures=================
		for(int i=0;i<cMonitor->getTempsCount();i++)
		{
			cMonitor->getTemps(&sensor,i);
			lstrcpyA(Temperatures[i].name,sensor.name);
			Temperatures[i].cur=sensor.pVar;
			if(Temperatures[i].cur>Temperatures[i].max)
				Temperatures[i].max=Temperatures[i].cur;
			if(Temperatures[i].cur<Temperatures[i].min)
				Temperatures[i].min=Temperatures[i].cur;
		}
		//================Voltages==================
		for(int i=0;i<cMonitor->getVoltsCount();i++)
		{
			cMonitor->getVolts(&sensor,i);
			lstrcpyA(Voltages[i].name,sensor.name);
			Voltages[i].cur=sensor.pVar;
			if(Voltages[i].cur>Voltages[i].max)
				Voltages[i].max=Voltages[i].cur;
			if(Voltages[i].cur<Voltages[i].min)
				Voltages[i].min=Voltages[i].cur;
		}

		//================System Tray==================
		_itoa_s((int)Temperatures[0].cur,buff,127,10);
		ctray->setIcon(CreateSmallIcon(hwnd,buff));

		sprintf_s(buff,"%s: %d\n%s: %d\n%s: %d",Temperatures[0].name,(int)Temperatures[0].cur,Temperatures[1].name,(int)Temperatures[1].cur,Temperatures[2].name,(int)Temperatures[2].cur);
		ctray->setHint(buff);
		ctray->refresh();
		
		if(IsWindowVisible(hwnd))
		{
			OnTimer();//workstab.h
		}
		break;
	case WM_COMMAND:
			switch(wParam)
			{
			case ID_MENU_EXIT:
				delete ctray;
				SendMessage(hwnd,WM_DESTROY,0,0);
				PostQuitMessage(0);
				return 0;
			case ID_MENU_HIDE:
				SendMessage(hwnd,WM_CLOSE,0,0);
				break;
			case ID_MENU_RESTORE:
				ShowWindow(hwnd,SW_RESTORE);
				break;
			case IDBUTTON1:
				break;
			}
		break;
	case WM_NOTIFY:
		OnNotifyTab(hwnd, wParam, lParam);
		break;
	case WM_TRAY:
		 switch((UINT)lParam)
        {
        case WM_MOUSEMOVE:
			break;
        case WM_LBUTTONDOWN:
			break;
        case WM_LBUTTONUP:
			break;
        case WM_LBUTTONDBLCLK:
			break;
        case WM_RBUTTONDOWN:
			SetForegroundWindow(hwnd);//для пропадания при убитом фокусе
			POINT p;
			GetCursorPos(&p);
			TrackPopupMenu(popup,TPM_LEFTALIGN,p.x,p.y,0,hwnd,NULL);
			break;
        case WM_RBUTTONUP:
			break;
        case WM_RBUTTONDBLCLK:
			break;
        case WM_CONTEXTMENU:
			break;
        }
		break;
	}

	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int GetFilePath(char *FileDir,const char *FileName)
{
	int slen=strlen(FileName);
	for(int i=slen-1;i>0;i--)
	{
		if(FileName[i]=='\\')
		{
			for(int j=0;j<i;j++)
			{
				FileDir[j]=FileName[j];
			}
			FileDir[i]='\0';
			break;
		}
	}
	return -1;
}

int APIENTRY WinMain(  
    HINSTANCE hinstance,  // handle of current instance  
    HINSTANCE hinstPrev,  // handle of previous instance 
    LPSTR lpCmdLine,      // address of command-line string 
    int nCmdShow)         // show-window type 
{
	flog=NULL;

	if(FindWindow("SysMonitorClass","SysMonitor")!=NULL) return -1;

	char BUFFER[MAX_PATH];
	GetModuleFileName(NULL,BUFFER,MAX_PATH);
	GetFilePath(CurDir,BUFFER);

	if(lstrcmp(lpCmdLine,"log")==0)
	{
		MessageBox(0,lpCmdLine,"Cmd Line",0);
		ZeroMemory(BUFFER,sizeof(BUFFER));
		sprintf_s(BUFFER,"%s\\log.txt",CurDir);
		flog=new fstream(BUFFER,ios::app);
		ZeroMemory(BUFFER,sizeof(BUFFER));
		sprintf_s(BUFFER,"New record!!!\n");
		flog->write(BUFFER,lstrlen(BUFFER));

	}
	
	WNDCLASS wc; 
	MSG msg;

	hinst=hinstance;

	InitCommonControls();

    // Register the main window class. 
    wc.style = CS_HREDRAW | CS_VREDRAW; 
    wc.lpfnWndProc = (WNDPROC) MainWndProc; 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance = hinstance; 

    wc.hIcon = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON1)); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName = (LPCSTR) NULL; 
    wc.lpszClassName = "SysMonitorClass"; 
 
    if (!RegisterClass(&wc)) 
       return FALSE; 

	MainWnd=CreateWindowEx(WS_EX_TOPMOST,wc.lpszClassName,"SysMonitor",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,50,50,250,250,0,0,hinstance,0);
	if(!MainWnd) 
	{
			MessageBox(NULL,"Can't create window","Error!",MB_OK);
			return -1;
	}
	ShowWindow(MainWnd,SW_SHOW);

	UpdateWindow(MainWnd);

    // 
    // Process other messages. 
    // 

	while (GetMessage(&msg, (HWND)0, 0, 0)) 
    { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 
 
    // Return the exit code to Windows. 
	destroyApp();
    return msg.wParam; 
}