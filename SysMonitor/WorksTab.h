/*
	*	Работа с вкладками, иницилизация, обработка сообщений  и пр.	*
*/
#ifndef WORKSTAB_H
#define WORKSTAB_H

#include <Windows.h>
#include <CommCtrl.h>
#include <Monitoring.h>
#include <stdlib.h>

void InitTabs(HINSTANCE hinst,HWND hwndParent);

void FreeTabs();

HWND DoCreateTabControl(HWND hwndParent);

HWND DoCreateDisplayWindow(HWND hwndTab);

BOOL OnNotifyTab(HWND hwndDisplay, WPARAM wParam, LPARAM lParam);

void OnTimer();

void SetTabActive(int);

void ShowSetting(bool);

#endif