#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "ttk/widget.h" // TtkWidget

class NumberedWidget : public TtkWidget
{
public:
	virtual ~NumberedWidget();
	static NumberedWidget* NewL(CSymTtkWsEnv& ws_env,
				     const TRect& rect, TInt num,
				     CSymTtkWindow* window);
	static NumberedWidget* NewLC(CSymTtkWsEnv& ws_env,
				      const TRect& rect, TInt num,
				      CSymTtkWindow* parent);
public: /* from TtkWidget */
	void handle_redraw_event(const TRect& pect);
private:
	NumberedWidget(CSymTtkWsEnv& ws_env, const TRect& rect, TInt num);
private:
	TInt num_;
};

#endif // NUMBEREDWIDGET_H
