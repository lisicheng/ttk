#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "window/widget.h" // CWidget

class CNumberedWidget;
class CWindow;
class CWsClient;

class CMainWidget : public CWidget
{
public:
	virtual ~CMainWidget();
	static CMainWidget* NewL(CWsClient& aWsEnv, const CWindow* aParent,
				 const TRect& aRect);
	static CMainWidget* NewLC(CWsClient& aWsEnv, const CWindow* aParent,
				  const TRect& aRect);
public: /* from CWidget */
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
private:
	CMainWidget(CWsClient& aWsEnv);
	void ConstructL(const CWindow* aParent, const TRect& aRect);
private:
	CNumberedWidget* iComponent;
};

#endif // MAINWIDGET_H
