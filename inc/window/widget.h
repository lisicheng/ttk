#ifndef WIDGET_H
#define WIDGET_H

#include <e32base.h> // CBase
#include <w32std.h> // TKeyEvent

class CWsClient;

class CWidget : public CBase
{
public:
	virtual ~CWidget();
public:
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
	void Draw(const TRect& aRect);
	CWindow* Window();
protected:
	CWidget(CWsClient& aWsEnv);
	void ConstructL();
private:
	CWsClient& iWsEnv;
	CWindow* iWindow;
	TBool iOwnWindow;
	TRect iRect;
};

#endif // WIDGET_H
