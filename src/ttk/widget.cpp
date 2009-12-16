#include "ttk/widget.h"

#include "ttk/common.h"
#include "ttk/gcinterface.h"
#include "ttk/windowinterface.h"
#include "ttk/wsenvinterface.h"

TtkWidget::~TtkWidget()
{
	if (own_window_)
		delete window_;
}

TtkWidget::TtkWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		     TtkWindowInterface* window)
		: ws_env_(ws_env), rect_(rect), window_(NULL),
		  own_window_(false), has_focus_(false)
{
	if (window) {
		window_ = window;
		own_window_ = false;
	} else {
		window_ = ws_env_.new_window(*this, kTtkColorWhite);
		own_window_ = true;
	}
}

void TtkWidget::handle_key_event(TtkKeyEvent& key_event)
{
}

void TtkWidget::handle_pointer_event(TtkPointerEvent& pointer_event)
{
}

void TtkWidget::handle_redraw_event(const TtkRect& rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.clear(rect);
}

bool TtkWidget::focusable() const
{
	return false;
}

bool TtkWidget::has_focus() const
{
	return has_focus_;
}

void TtkWidget::set_focus(bool has_focus)
{
	has_focus_ = has_focus;
}

TtkWsEnvInterface& TtkWidget::ws_env()
{
	return ws_env_;
}

const TtkRect& TtkWidget::rect() const
{
	return rect_;
}

void TtkWidget::set_rect(const TtkRect& rect)
{
	rect_ = rect;
}

TtkWindowInterface& TtkWidget::window() const
{
	return *window_;
}

void TtkWidget::refresh_rect(const TtkRect& rect1, const TtkRect& rect2)
{
}
