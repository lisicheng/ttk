#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "window/widget.h" // CWidget

class CNumberedWidget;

class CMainWidget : public CWidget
{
public:
	virtual ~CMainWidget();
public: /* from CWidget */
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
	void Draw(const TRect& aRect);
private:
	CNumberedWidget* iComponent;
}

#endif // MAINWIDGET_H
