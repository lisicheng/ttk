#ifndef WINDOW_H
#define WINDOW_H

#include <e32base.h> // CBase
#include <w32std.h> // TPointerEvent

class CWsClient;

class CWindow : public CBase
{
public:
	enum {
		KPointerMoveBufferSize = 32
	};
public:
	virtual ~CWindow();
public:
	RWindow& Window(); // our own window
	CWindowGc* SystemGc(); // system graphics context
	CWsScreenDevice* Screen();
	CFont* Font();
public:
	// drawing
	virtual void Draw(const TRect& aRect) = 0;
	virtual void HandlePointerEvent (TPointerEvent& aPointerEvent) = 0;
protected:
	CWindow(CWsClient* aClient);
	void ConstructL(const TRect& aRect, const TRgb& aColor, CWindow* aParent=0);
private:
	RWindow iWindow; // window server window
	CWsClient* iClient; // client including session and group
	CFont* iFont;
};

#endif // WINDOW_H
