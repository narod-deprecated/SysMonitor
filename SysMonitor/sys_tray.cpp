#include "sys_tray.h"

cTray::cTray(HWND wnd,UINT ID)
{
	ZeroMemory(&nid,sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(nid);
	nid.hWnd=wnd;
	nid.uID=ID;
	nid.uFlags=NIF_TIP | NIF_ICON | NIF_MESSAGE;
	nid.uVersion=NOTIFYICON_VERSION;
};

void cTray::setHint(const char * const text)
{
	lstrcpy(nid.szTip,text);
};
void cTray::setIcon(HICON icon)
{
	nid.hIcon=icon;
};

void cTray::setCallbackMessage(UINT cmsg)
{
	nid.uCallbackMessage=cmsg;
};

BOOL cTray::show()
{
	BOOL ret=(BOOL)Shell_NotifyIcon(NIM_ADD,&nid);
	if(nid.hIcon)
		DestroyIcon(nid.hIcon);
	return ret;
};

BOOL cTray::refresh()
{
	BOOL ret=(BOOL)Shell_NotifyIcon(NIM_MODIFY,&nid);
	if(nid.hIcon)
		DestroyIcon(nid.hIcon);
	return ret;
};

cTray::~cTray()
{
	Shell_NotifyIcon(NIM_DELETE,&nid);
	
	if(nid.hIcon)
		DestroyIcon(nid.hIcon);
	
	ID_TRAY=0;
	hwnd=0;
};