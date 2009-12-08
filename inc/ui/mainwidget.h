#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "window/widget.h" // CWidget

class CNumberedWidget;

class CMainWidget : public CWidget
{
public:
	virtual ~CMainWidget();
	static CMainWidget* NewL(CWsClient& aWsEnv, const TRect& aRect);
	static CMainWidget* NewLC(CWsClient& aWsEnv, const TRect& aRect);
private:
	CMainWidget(CWsClient& aWsEnv, const TRect& aRect);
	void ConstructL();
private: /* from CWidget */
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
	void Draw(const TRect& aRect);
private:
	CNumberedWidget* iComponent;
};

#endif // MAINWIDGET_H
