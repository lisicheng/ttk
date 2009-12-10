#ifndef TTK_WIDGET_H
#define TTK_WIDGET_H

#include <e32base.h> // CBase
#include <w32std.h> // TKeyEvent
#include "ttk/common/rect.h" // TtkRect
#include "ttk/common/keyevent.h" // TtkKeyEvent

class CSymTtkWsEnv;
class TtkPointerEvent;
class TtkWindowInterface;

class TtkWidget : public CBase
{
public:
	virtual ~TtkWidget();
	static TtkWidget* NewL(CSymTtkWsEnv& ws_env, const TtkRect& rect,
			     TtkWindowInterface* window);
	static TtkWidget* NewLC(CSymTtkWsEnv& ws_env, const TtkRect& rect,
			      TtkWindowInterface* window);
public:
	virtual void handle_key_event(TtkKeyEvent& key_event);
	virtual void handle_pointer_event(TtkPointerEvent& pointer_event);
	virtual void handle_redraw_event(const TtkRect& rect);
public:
	CSymTtkWsEnv& ws_env();
	const TtkRect& rect() const;
	void set_rect(const TtkRect& rect);
protected:
	TtkWidget(CSymTtkWsEnv& ws_env, const TtkRect& rect);
	void ConstructL(TtkWindowInterface* window);
protected:
	TtkWindowInterface& window() const;
private:
	CSymTtkWsEnv& ws_env_;
	TtkRect rect_;
	TtkWindowInterface* window_;
	bool own_window_;
};

#endif // TTK_WIDGET_H
