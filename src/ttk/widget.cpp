#include "ttk/widget.h"

#include "symttk/window.h"
#include "symttk/wsenv.h"

TtkWidget::~TtkWidget()
{
	if (own_window_)
		delete window_;
}

TtkWidget* TtkWidget::NewL(CSymTtkWsEnv& ws_env, const TRect& rect, CSymTtkWindow* window)
{
	TtkWidget* self = TtkWidget::NewLC(ws_env, rect, window);
	CleanupStack::Pop(self);
	return self;
}

TtkWidget* TtkWidget::NewLC(CSymTtkWsEnv& ws_env, const TRect& rect, CSymTtkWindow* window)
{
	TtkWidget* self = new(ELeave) TtkWidget(ws_env, rect);
	CleanupStack::PushL(self);
	self->ConstructL(window);
	return self;
}

void TtkWidget::handle_key_event(TKeyEvent& key_event)
{
	return;
}

void TtkWidget::handle_pointer_event(TPointerEvent& pointer_event)
{
	return;
}

void TtkWidget::handle_redraw_event(const TRect& rect)
{
	CWindowGc& gc = ws_env().Gc();
	gc.Clear(rect);
}

CSymTtkWsEnv& TtkWidget::ws_env()
{
	return ws_env_;
}

const TRect& TtkWidget::rect() const
{
	return rect_;
}

void TtkWidget::set_rect(const TRect& rect)
{
	rect_ = rect;
}

TtkWidget::TtkWidget(CSymTtkWsEnv& ws_env, const TRect& rect)
		: ws_env_(ws_env), rect_(rect)
{
}

void TtkWidget::ConstructL(CSymTtkWindow* window)
{
	if (window) {
		window_ = window;
		own_window_ = false;
	} else {
		window_ = CSymTtkWindow::NewL(*this, KRgbWhite);
		own_window_ = true;
	}
}

CSymTtkWindow& TtkWidget::window() const
{
	return *window_;
}
