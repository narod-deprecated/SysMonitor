/*
**	Данный заголовок содержит класс для работы с Tooltip  **
**	Автор:	Сычёв Виталий	Дата:	27.07.2014			  ** 
*/

#include <Windows.h>
#include <CommCtrl.h>

#ifndef _TOOLTIP_H_
#define _TOOLTIP_H_

class cToolTip
{
public:
	cToolTip(HWND hwndParent,HINSTANCE hinstance);
	cToolTip(HWND hwndParent,char* hint,HINSTANCE hinstance);
	~cToolTip(void);
	void setTextHint(char* hint);
	void deleteTextHint();
private:
	HWND WndToolTip;
	HWND WndParent;
	HINSTANCE hinst;
};

#endif

