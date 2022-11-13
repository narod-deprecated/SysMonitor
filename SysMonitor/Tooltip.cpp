#include "Tooltip.h"

cToolTip::cToolTip(HWND hwndParent,HINSTANCE hinstance)
{
	cToolTip(hwndParent,NULL,hinstance);//создаем без текста
};

cToolTip::cToolTip(HWND hwndParent,char* hint,HINSTANCE hinstance)
{
	WndParent=hwndParent;
	hinst=hinstance;
	if(!hinst||!WndParent)
		MessageBox(0,0,0,0);
	WndToolTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, 
                                 WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, 
                                 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                                 hwndParent, NULL, hinst,NULL);


    SetWindowPos(WndToolTip, HWND_TOPMOST, 0, 0, 0, 0, 
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    // Set up "tool" information. In this case, the "tool" is the entire parent window.
    
    TOOLINFO ti = { 0 };
    ti.cbSize   = sizeof(TOOLINFO);
    ti.uFlags   = TTF_SUBCLASS;
	//ti.uId		= 
    ti.hwnd     = hwndParent;
    ti.hinst    = hinst;
	if(hint)
	{
		ti.lpszText=hint;
	}
	else 
		ti.lpszText=LPSTR_TEXTCALLBACK;
    GetClientRect (hwndParent, &ti.rect);

    // Associate the tooltip with the "tool" window.
    SendMessage(WndToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);
};
cToolTip::~cToolTip(void)
{

};
void cToolTip::setTextHint(char* hint)
{
	TOOLINFO ti = { 0 };
    ti.cbSize   = sizeof(TOOLINFO);
    ti.uFlags   = TTF_SUBCLASS;
    ti.hwnd     = WndParent;
    ti.hinst    = hinst;

	ti.lpszText=hint;

    GetClientRect (WndParent, &ti.rect);

    // Associate the tooltip with the "tool" window.
    SendMessage(WndToolTip, TTM_UPDATETIPTEXT, 0, (LPARAM) (LPTOOLINFO) &ti);
};

void cToolTip::deleteTextHint()
{
	TOOLINFO ti = { 0 };
    ti.cbSize   = sizeof(TOOLINFO);
    ti.uFlags   = TTF_SUBCLASS;
    ti.hwnd     = WndParent;
    ti.hinst    = hinst;

    //GetClientRect (WndParent, &ti.rect);

    // Associate the tooltip with the "tool" window.
    SendMessage(WndToolTip, TTM_DELTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);
};
