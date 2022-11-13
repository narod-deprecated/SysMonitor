//******Здесь находятся функции для работы с системным лотком******\\

#ifndef _SYS_TRAY_H_
#define _SYS_TRAY_H_
#include <Windows.h>

class cTray
{
private:
	int ID_TRAY;
	NOTIFYICONDATA nid;
	HWND hwnd;
public:
	cTray(HWND,UINT);
	~cTray();
	void setHint(const char * const);//Назначаем подсказку
	void setIcon(HICON);//Назначаем иконку
	void setCallbackMessage(UINT);//callback-функция
	BOOL show();
	BOOL refresh();
};

#endif