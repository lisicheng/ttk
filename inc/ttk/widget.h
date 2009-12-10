#ifndef TTK_WIDGET_H
#define TTK_WIDGET_H

#include <e32base.h> // CBase
#include <w32std.h> // TKeyEvent

class CSymTtkWsEnv;
class CSymTtkWindow;

class TtkWidget : public CBase
{
public:
	virtual ~TtkWidget();
	static TtkWidget* NewL(CSymTtkWsEnv& aWsClient, const TRect& aRect,
			     CSymTtkWindow* aWindow);
	static TtkWidget* NewLC(CSymTtkWsEnv& aWsClient, const TRect& aRect,
			      CSymTtkWindow* aWindow);
public:
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent);
	virtual void HandlePointerEventL(TPointerEvent& aPointerEvent);
	virtual void Draw(const TRect& aRect);
	CSymTtkWsEnv& WsEnv();
	const TRect& Rect() const;
	void SetRect(const TRect& aRect);
protected:
	TtkWidget(CSymTtkWsEnv& aWsEnv, const TRect& aRect);
	void ConstructL(CSymTtkWindow* aWindow);
protected:
	CSymTtkWindow& Window() const;
private:
	CSymTtkWsEnv& iWsEnv;
	TRect iRect;
	CSymTtkWindow* iWindow;
	TBool iOwnWindow;
};

#endif // TTK_WIDGET_H
