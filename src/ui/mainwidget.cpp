#include "ui/mainwidget.h"

#include "common.h"
#include "ui/numberedwidget.h"
#include "symttk/window.h"

MainWidget::~MainWidget()
{
	delete component_;
}

MainWidget* MainWidget::NewL(CSymTtkWsEnv& ws_env, const TRect& rect)
{
	MainWidget* self = MainWidget::NewLC(ws_env, rect);
	CleanupStack::Pop(self);
	return self;
}

MainWidget* MainWidget::NewLC(CSymTtkWsEnv& ws_env, const TRect& rect)
{
	MainWidget* self = new(ELeave) MainWidget(ws_env, rect);
	self->ConstructL();
	CleanupStack::PushL(self);
	return self;
}

MainWidget::MainWidget(CSymTtkWsEnv& ws_env, const TRect& rect)
		: TtkWidget(ws_env, rect)
{
}

void MainWidget::ConstructL()
{
	TtkWidget::ConstructL(NULL);
	TRect rect(rect());
	rect.Resize(-100, -100);
	rect.Move(50, 50);
	component_ = NumberedWidget::NewL(ws_env(), rect, 3, &window());
}

void MainWidget::handle_key_event(TKeyEvent& key_event)
{
	TRect rect(component_->rect());
	switch (key_event.iCode) {
	case EKeyUpArrow:
		rect.Move(0, -10);
		component_->set_rect(rect);
		rect.Resize(0, 10);
		window().Window().Invalidate(rect);
		break;
	case EKeyDownArrow:
		rect.Move(0, 10);
		component_->set_rect(rect);
		rect.Move(0, -10);
		rect.Resize(0, 10);
		window().Window().Invalidate(rect);
		break;
	default:
		break;
	}
}

void MainWidget::handle_redraw_event(const TRect& rect)
{
	TtkWidget::handle_redraw_event(rect);
	component_->handle_redraw_event(rect);
}
