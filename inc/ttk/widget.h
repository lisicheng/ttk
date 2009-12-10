#ifndef TTK_WIDGET_H
#define TTK_WIDGET_H

#include <e32base.h> // CBase
#include <w32std.h> // TKeyEvent

class CWsClient;
class CWindow;

class CWidget : public CBase
{
public:
	virtual ~CWidget();
	static CWidget* NewL(CWsClient& aWsClient, const TRect& aRect,
			     CWindow* aWindow);
	static CWidget* NewLC(CWsClient& aWsClient, const TRect& aRect,
			      CWindow* aWindow);
public:
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent);
	virtual void HandlePointerEventL(TPointerEvent& aPointerEvent);
	virtual void Draw(const TRect& aRect);
	CWsClient& WsEnv();
	const TRect& Rect() const;
	void SetRect(const TRect& aRect);
protected:
	CWidget(CWsClient& aWsEnv, const TRect& aRect);
	void ConstructL(CWindow* aWindow);
protected:
	CWindow& Window() const;
private:
	CWsClient& iWsEnv;
	TRect iRect;
	CWindow* iWindow;
	TBool iOwnWindow;
};

#endif // TTK_WIDGET_H
