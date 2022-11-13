//******����� ��������� ������� ��� ������ � ��������� ������******\\

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
	void setHint(const char * const);//��������� ���������
	void setIcon(HICON);//��������� ������
	void setCallbackMessage(UINT);//callback-�������
	BOOL show();
	BOOL refresh();
};

#endif