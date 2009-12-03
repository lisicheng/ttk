#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window/window.h" // CWindow

class CMainWindow : public CWindow
{
public:
	CMainWindow (CWsClient* aClient);
	~CMainWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
};

#endif // MAINWINDOW_H
