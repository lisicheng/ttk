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
public:
	enum EScrollDir {Up, Down};
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
	void HandlePointerMoveBufferReady () {}
private:
	CNumberedWindow(CWsClient& aClient, TInt aNum);
private:
	static TInt iCount;
	TInt	iNumber;	// Number displayed in window
	TPoint	iOldPos;	// Position is required for drag and drop
	TPoint	iOffset;	// Used for scrolling
	TRect	iRepeatRect;	// Boundary for pointer repeat events
	EScrollDir	iScrollDir;	// Scroll direction for pointer repeat events
};

#endif // NUMBEREDWINDOW_H
