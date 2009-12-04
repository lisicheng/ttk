#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window/window.h" // CWindow

class CMainWindow : public CWindow
{
public:
	static CMainWindow* NewL(CWsClient& aClient, const TRect& aRect,
				 const TRgb& aColor, CWindow* aParent = 0);
	static CMainWindow* NewLC(CWsClient& aClient, const TRect& aRect,
				  const TRgb& aColor, CWindow* aParent = 0);
public: /* from CWindow */
	void Draw(const TRect& aRect);
	void HandlePointerEvent(TPointerEvent& aPointerEvent);
private:
	CMainWindow(CWsClient& aClient);
};

#endif // MAINWINDOW_H
