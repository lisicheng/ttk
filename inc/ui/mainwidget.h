#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ttk/widget.h" // TtkWidget

class NumberedWidget;

class MainWidget : public TtkWidget
{
public:
	virtual ~MainWidget();
	static MainWidget* NewL(CSymTtkWsEnv& ws_env, const TRect& rect);
	static MainWidget* NewLC(CSymTtkWsEnv& ws_env, const TRect& rect);
private:
	MainWidget(CSymTtkWsEnv& ws_env, const TRect& rect);
	void ConstructL();
private: /* from TtkWidget */
	void handle_key_event(TKeyEvent& key_event);
	void handle_redraw_event(const TRect& rect);
private:
	NumberedWidget* component_;
};

#endif // MAINWIDGET_H
