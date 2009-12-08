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
	static CWidget* NewL(CWsClient& aWsClient, const TRect& aRect,
			     const CWindow* aWindow);
	static CWidget* NewLC(CWsClient& aWsClient, const TRect& aRect,
			      const CWindow* aWindow);
public:
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent);
	virtual void Draw(const TRect& aRect);
	CWsClient& WsEnv();
	const TRect& Rect() const;
protected:
	CWidget(CWsClient& aWsEnv, const TRect& aRect);
	void ConstructL(const CWindow* aWindow);
protected:
	void SetRect(TRect& aRect);
	const CWindow& Window() const;
private:
	CWsClient& iWsEnv;
	TRect iRect;
	const CWindow* iWindow;
	TBool iOwnWindow;
};

#endif // WIDGET_H
