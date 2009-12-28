#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ttk/widget.h" /* TtkWidget */

class NumberedWidget;

class MainWidget : public TtkWidget
{
public:
	virtual ~MainWidget();
	MainWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect);
private: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& redraw_rect);
private:
	TtkWidget* component_;
	TtkWidget* text_;
};

#endif /* MAINWIDGET_H */
