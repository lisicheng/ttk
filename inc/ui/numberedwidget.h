#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "ttk/widget.h" // TtkWidget

class NumberedWidget : public TtkWidget
{
public:
	virtual ~NumberedWidget();
	static NumberedWidget* NewL(CSymTtkWsEnv& ws_env,
				     const TtkRect& rect, int num,
				     TtkWindowInterface* window);
	static NumberedWidget* NewLC(CSymTtkWsEnv& ws_env,
				      const TtkRect& rect, int num,
				      TtkWindowInterface* parent);
public: /* from TtkWidget */
	void handle_redraw_event(const TtkRect& pect);
private:
	NumberedWidget(CSymTtkWsEnv& ws_env, const TtkRect& rect, int num);
private:
	int num_;
};

#endif // NUMBEREDWIDGET_H
