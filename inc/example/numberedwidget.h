#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "ttk/widget.h" /* TtkWidget */

class TtkWsEnvInterface;

class NumberedWidget : public TtkWidget
{
public:
	virtual ~NumberedWidget();
	NumberedWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		       int num, TtkWidget* parent);
public: /* from TtkWidget */
	void handle_redraw_event(const TtkRect& redraw_rect);
private:
	int num_;
};

#endif /* NUMBEREDWIDGET_H */
