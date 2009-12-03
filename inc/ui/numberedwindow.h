#ifndef NUMBEREDWINDOW_H
#define NUMBEREDWINDOW_H

#include "window/window.h" // CWindow

class CNumberedWindow : public CWindow
{
public:
	enum EScrollDir {Up, Down};
	CNumberedWindow (CWsClient* aClient, TInt aNum);
	~CNumberedWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
	void HandlePointerMoveBufferReady () {}
private:
	static TInt iCount;
	TInt	iNumber;	// Number displayed in window
	TPoint	iOldPos;	// Position is required for drag and drop
	TPoint	iOffset;	// Used for scrolling
	TRect	iRepeatRect;	// Boundary for pointer repeat events
	EScrollDir	iScrollDir;	// Scroll direction for pointer repeat events
};

#endif // NUMBEREDWINDOW_H
