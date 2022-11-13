#include "Constantes.h"

CHWMonitor *cMonitor=NULL;

sSENSOR Temperatures[10];
sSENSOR Voltages[10];

bool StartWithStartup=0;
int ColorIconSysTray=0;

HINSTANCE hinst;

HWND MainWnd;
HWND MainTab;

HWND hLabels[10];
cToolTip* hTooltips[10];

char CurDir[MAX_PATH];

bool createLOG=false;