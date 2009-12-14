#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "ttk/widget.h" /* TtkWidget */

class TtkWsEnvInterface;

class NumberedWidget : public TtkWidget
{
public:
	virtual ~NumberedWidget();
	NumberedWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		       int num, TtkWindowInterface* window);
public: /* from TtkWidget */
	void handle_redraw_event(const TtkRect& rect);
private:
	int num_;
};

#endif /* NUMBEREDWIDGET_H */
