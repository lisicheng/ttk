#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ttk/widget.h" // TtkWidget

class NumberedWidget;

class MainWidget : public TtkWidget
{
public:
	virtual ~MainWidget();
	static MainWidget* NewL(TtkWsEnvInterface& ws_env, const TtkRect& rect);
	static MainWidget* NewLC(TtkWsEnvInterface& ws_env, const TtkRect& rect);
private:
	MainWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect);
	void ConstructL();
private: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& rect);
private:
	NumberedWidget* component_;
};

#endif // MAINWIDGET_H
