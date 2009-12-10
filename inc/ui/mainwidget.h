#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ttk/widget.h" // TtkWidget

class CNumberedWidget;

class CMainWidget : public TtkWidget
{
public:
	virtual ~CMainWidget();
	static CMainWidget* NewL(CSymTtkWsEnv& aWsEnv, const TRect& aRect);
	static CMainWidget* NewLC(CSymTtkWsEnv& aWsEnv, const TRect& aRect);
private:
	CMainWidget(CSymTtkWsEnv& aWsEnv, const TRect& aRect);
	void ConstructL();
private: /* from TtkWidget */
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
	void Draw(const TRect& aRect);
private:
	CNumberedWidget* iComponent;
};

#endif // MAINWIDGET_H
