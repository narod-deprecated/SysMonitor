#include "draw_utils.h"

HICON CreateSmallIcon( HWND hWnd,const char szText[])
{
    HDC hdc, hdcMem;
    HBITMAP hBitmap = NULL;
    HBITMAP hOldBitMap = NULL;
    HBITMAP hBitmapMask = NULL;
    ICONINFO iconInfo;
    HFONT hFont;
    HICON hIcon;

    hdc = GetDC ( hWnd );
    hdcMem = CreateCompatibleDC ( hdc );
    hBitmap = CreateCompatibleBitmap ( hdc, 16, 16 );
    hBitmapMask = CreateCompatibleBitmap ( hdc, 16, 16 );
    ReleaseDC ( hWnd, hdc );
    hOldBitMap = (HBITMAP) SelectObject ( hdcMem, hBitmap );
    PatBlt ( hdcMem, 0, 0, 16, 16, BLACKNESS);

	RECT rect;
	SetRect(&rect,0,0,16,16);
	FillRect(hdcMem,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
    // Draw Text
	hFont = CreateFont(16,0,0,0,0,0,0,0,0,0,0,0,0,"Times New Roman");
    SelectObject ( hdcMem, hFont );
	SetBkColor(hdcMem,RGB(255,0,0));
	SetBkMode(hdcMem,TRANSPARENT);
    TextOut ( hdcMem, 0, 0, szText, lstrlen (szText) );

    SelectObject ( hdc, hOldBitMap );
    hOldBitMap = NULL;

    iconInfo.fIcon = TRUE;
    iconInfo.xHotspot = 0;
    iconInfo.yHotspot = 0;
    iconInfo.hbmMask = hBitmapMask;
    iconInfo.hbmColor = hBitmap;

    hIcon = CreateIconIndirect ( &iconInfo );

    DeleteObject ( SelectObject ( hdcMem, hFont ) );
    DeleteDC ( hdcMem );
    DeleteDC ( hdc );
    DeleteObject ( hBitmap );
    DeleteObject ( hBitmapMask );

    return hIcon;
}
