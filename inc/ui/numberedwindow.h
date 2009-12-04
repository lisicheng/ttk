#ifndef NUMBEREDWINDOW_H
#define NUMBEREDWINDOW_H

#include "window/window.h" // CWindow

class CNumberedWindow : public CWindow
{
public:
	static CNumberedWindow* NewL(CWsClient& aClient, TInt aNum,
				     const TRect& aRect, const TRgb& aColor,
				     CWindow* aParent = 0);
	static CNumberedWindow* NewLC(CWsClient& aClient, TInt aNum,
				      const TRect& aRect, const TRgb& aColor,
				      CWindow* aParent = 0);
public: /* from CWindow */
	void Draw(const TRect& aRect);
	void HandlePointerEvent(TPointerEvent& aPointerEvent);
private:
	CNumberedWindow(CWsClient& aClient, TInt aNum);
private:
	TInt iNumber; // Number displayed in window
	TPoint iOffset; // Used for scrolling
	TRect iRepeatRect; // Boundary for pointer repeat events
	enum {Up, Down} iScrollDir; // Scroll direction
};

#endif // NUMBEREDWINDOW_H
