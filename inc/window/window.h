#ifndef WINDOW_H
#define WINDOW_H

#include <e32base.h> // CBase
#include <w32std.h> // TPointerEvent

class CWsClient;
class CWindow;

class CWindow : public CBase
{
public:
	enum {KPointerMoveBufferSize=32};
	CWindow(CWsClient* aClient);
	void ConstructL(const TRect& aRect, const TRgb& aColor, CWindow* aParent=0);
	~CWindow();
	// access
	RWindow& Window(); // our own window
	CWindowGc* SystemGc(); // system graphics context
	CWsScreenDevice* Screen();
	CFont* Font();
	// drawing
	virtual void Draw(const TRect& aRect) = 0;
	virtual void HandlePointerEvent (TPointerEvent& aPointerEvent) = 0;
protected:
	RWindow iWindow; // window server window
	TRect iRect; // window's extent
private:
	CWsClient* iClient; // client including session and group
	CFont*	iFont;
};

#endif // WINDOW_H
