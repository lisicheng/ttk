#ifndef TTK_WIDGET_H
#define TTK_WIDGET_H

#include "ttk/common/keyevent.h" /* TtkKeyEvent */
#include "ttk/common/rect.h" /* TtkRect */

class TtkPointerEvent;
class TtkWindowInterface;
class TtkWsEnvInterface;

class TtkWidget
{
public:
	virtual ~TtkWidget();
	TtkWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		  TtkWindowInterface* window);
public:
	virtual void handle_key_event(TtkKeyEvent& key_event);
	virtual void handle_pointer_event(TtkPointerEvent& pointer_event);
	virtual void handle_redraw_event(const TtkRect& rect);
	virtual bool focusable() const;
	virtual void refresh_rect(const TtkRect& rect1, const TtkRect& rect2);
public:
	bool has_focus() const;
	void set_focus(bool has_focus);
	TtkWsEnvInterface& ws_env();
	const TtkRect& rect() const;
	void set_rect(const TtkRect& rect);
protected:
	TtkWindowInterface& window() const;
private:
	TtkWsEnvInterface& ws_env_;
	TtkRect rect_;
	TtkWindowInterface* window_;
	bool own_window_;
	bool has_focus_;
};

#endif /* TTK_WIDGET_H */
