#include "WorksTab.h"
#include "Constantes.h"
#include "strutil.h"
#include <stdlib.h>


static WNDPROC wpOrigTabProc;

// Subclass procedure 
  LRESULT APIENTRY TabCtrlSubclassProc(
      HWND hwnd, 
      UINT uMsg, 
      WPARAM wParam, 
      LPARAM lParam) 
  {

	  switch(uMsg)
	  {
	  case WM_CTLCOLORSTATIC:
			  return NULL;//Прозрачный фон под Static
		  break;
	  }
	  return CallWindowProc(wpOrigTabProc, hwnd, uMsg, 
		  wParam, lParam); 
  } 


void InitTabs(HINSTANCE hinst,HWND hwndParent)
{
	RECT rArea;
	GetClientRect(hwndParent,&rArea);
	MainTab=CreateWindow( WC_TABCONTROL ,"",WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
		2,2,rArea.right-4,rArea.bottom-4,hwndParent,(HMENU)IDMAINTAB,hinst,NULL);
	
	TCITEM tci;
	//tci.iImage=(int)LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON1));
	tci.mask = TCIF_TEXT | TCIF_IMAGE; 
	tci.iImage = -1; 
	tci.pszText = "Temperatures"; 
	TabCtrl_InsertItem(MainTab,0,(const TCITEM*)&tci);

	tci.pszText = "Volts"; 
	TabCtrl_InsertItem(MainTab,1,(const TCITEM*)&tci);

	//tci.pszText = "Speeds"; 
	//TabCtrl_InsertItem(MainTab,2,(const TCITEM*)&tci);

	//tci.pszText = "Setting"; 
	//TabCtrl_InsertItem(MainTab,3,(const TCITEM*)&tci);

	tci.pszText = "About"; 
	TabCtrl_InsertItem(MainTab,2,(const TCITEM*)&tci);
	//TabCtrl_SetItem(TempPanel,1,(const TCITEM*)&tci);

	for(int i=0;i<10;i++)
	{
		hLabels[i]=CreateWindowEx(WS_EX_CONTROLPARENT,WC_STATIC,"UNKNOWN",WS_CHILD | WS_VISIBLE | 
			SS_NOTIFY,10,(i*35)+30,75,35,MainTab,0,hinst,NULL);
		hTooltips[i]=new cToolTip(hLabels[i],NULL,hinst);
	}
    wpOrigTabProc = (WNDPROC) SetWindowLong(MainTab,
		GWL_WNDPROC, (LONG) TabCtrlSubclassProc);
	SetTabActive(0);
}

void FreeTabs()
{
	for(int i=0;i<10;i++)
		delete hTooltips[i];
	SetWindowLong(MainTab, GWL_WNDPROC, 
                  (LONG) wpOrigTabProc); 

}

BOOL OnNotifyTab(HWND hwndDisplay, WPARAM wParam, LPARAM lParam)
{
	if((int)wParam==IDMAINTAB)
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case TCN_SELCHANGE:
				SetTabActive(TabCtrl_GetCurSel(MainTab)); 
				break;
			}
		}
	return TRUE;
}

void OnTimer()
{
	char buff[255];
	int cur=TabCtrl_GetCurSel(MainTab);
	switch(cur)
	{
	case 0:
		for(int i=0;i<cMonitor->getTempsCount();i++)//(Temperatures[i].name[0]!=0&&i<10);i++)
		{
			sprintf_s(buff,255,"%s: %d",Temperatures[i].name,(int)Temperatures[i].cur);
			SetWindowText(hLabels[i],buff);
			sprintf_s(buff,255,"%s Min: %d Cur: %d Max: %d",Temperatures[i].name,(int)Temperatures[i].min,(int)Temperatures[i].cur,(int)Temperatures[i].max);
			hTooltips[i]->setTextHint(buff);
		}
		break;
	case 1:
		for(int i=0;i<cMonitor->getVoltsCount();i++)//(Temperatures[i].name[0]!=0&&i<10);i++)
		{
			sprintf_s(buff,255,"%s: %.3f",Voltages[i].name,Voltages[i].cur);
			SetWindowText(hLabels[i],buff);
			sprintf_s(buff,255,"%s Min: %.3f Cur: %.3f Max: %.3f",Voltages[i].name,Voltages[i].min,Voltages[i].cur,Voltages[i].max);
			hTooltips[i]->setTextHint(buff);
		}
		break;
	case 2:
		hTooltips[0]->setTextHint("");
		//sprintf_s(buff,255,"%s%2.2fv",TextLabels[3],CPUVCORE);
		//SetWindowText(hLabels[0],buff);
		//AppendHint(hLabels[0],buff);

		//sprintf_s(buff,255,"%s%2.2fv",TextLabels[4],VCC);
		//SetWindowText(hLabels[1],buff);
		//AppendHint(hLabels[1],buff);
		break;
	}
}

void SetTabActive(int index)
{
	RECT rect;
	for(int i=0;i<10;i++)
	{
		ShowWindow(hLabels[i],SW_HIDE);
	}
	switch(index)
	{
	case 0:
		for(int i=0;i<cMonitor->getTempsCount();i++){
			MoveWindow(hLabels[i],10,(i*35)+30,75,25,false);
			SetWindowText(hLabels[i],Temperatures[i].name);
			ShowWindow(hLabels[i],SW_SHOW);
		}
		break;
	case 1:
		for(int i=0;i<cMonitor->getVoltsCount();i++)
		{
			MoveWindow(hLabels[i],10,(i*35)+30,125,25,false);
			SetWindowText(hLabels[i],Voltages[i].name);
			ShowWindow(hLabels[i],SW_SHOW);
		}

		break;
	case 2:
		GetClientRect(MainTab,&rect);
		MoveWindow(hLabels[0],(rect.right-150)/2,rect.bottom/2,150,25,false);
		SetWindowText(hLabels[0],"Vendor: Sychov Vitaliy");
		ShowWindow(hLabels[0],SW_SHOW);
		break;
	case 3:

		break;
	case 4:
		
		break;
	}
}

void ShowSetting(bool flag)
{
	if(flag)
	{

	}
	else
	{

	}


}
