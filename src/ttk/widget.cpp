#include "ttk/widget.h"

#include "common.h"
#include "symttk/window.h"
#include "symttk/wsenv.h"
#include "symttk/gc.h"

TtkWidget::~TtkWidget()
{
	if (own_window_)
		delete window_;
}

TtkWidget* TtkWidget::NewL(TtkWsEnvInterface& ws_env, const TtkRect& rect, TtkWindowInterface* window)
{
	TtkWidget* self = new TtkWidget(ws_env, rect);
	self->ConstructL(window);
	return self;
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

TtkWidget::TtkWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect)
		: ws_env_(ws_env), rect_(rect), window_(NULL),
		  own_window_(false)
{
}

void TtkWidget::ConstructL(TtkWindowInterface* window)
{
	if (window) {
		window_ = window;
		own_window_ = false;
	} else {
		window_ = ws_env_.new_window(*this, kTtkColorWhite);
		own_window_ = true;
	}
}

TtkWindowInterface& TtkWidget::window() const
{
	return *window_;
}
