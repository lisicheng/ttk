#ifndef WIDGET_H
#define WIDGET_H

#include <e32base.h> // CBase
#include <w32std.h> // TKeyEvent

class CWsClient;
class CWindow;

class CWidget : public CBase
{
public:
	virtual ~CWidget();
public:
	CWindow& Window();
	CWsClient& WsEnv();
	TRect& Rect();
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
	void Draw(const TRect& aRect);
protected:
	CWidget(CWsClient& aWsEnv);
	void ConstructL(const CWindow* aWindow, const TRect& aRect);
private:
	CWsClient& iWsEnv;
	CWindow* iWindow;
	TBool iOwnWindow;
	TRect iRect;
};

#endif // WIDGET_H
