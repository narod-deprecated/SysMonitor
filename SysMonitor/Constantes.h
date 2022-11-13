#include <stdio.h>
#include <Windows.h>
#include "resource.h"
#include <Monitoring.h>
#include "Tooltip.h"
#include "sys_tray.h"
#include <fstream>

#ifndef _CONSTANTES_H_
#define _CONSTANTES_H_

struct sSENSOR{
	double min;
	double cur;
	double max;
	char name[32];
};

#define IDMAINTAB 6001

#define IDTIMER1 5001
#define IDBUTTON1 4554
#define IDTRAY1 6545
#define WM_TRAY (WM_APP + 1)

#define ID_MENU_EXIT 12901
#define ID_MENU_RESTORE 12902
#define ID_MENU_HIDE 12903



extern CHWMonitor *cMonitor;

extern sSENSOR Temperatures[];
extern sSENSOR Voltages[];

extern bool StartWithStartup;//обьявление глобальной переменной
extern int ColorIconSysTray;

extern HINSTANCE hinst;

extern HWND MainWnd;
extern HWND MainTab;
extern HWND hLabels[];
extern cToolTip* hTooltips[];

extern char CurDir[];

extern bool createLOG;

#endif
