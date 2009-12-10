#include "ui/mainwidget.h"

#include "common.h"
#include "ui/numberedwidget.h"
#include "symttk/window.h"

MainWidget::~MainWidget()
{
	delete component_;
}

MainWidget* MainWidget::NewL(CSymTtkWsEnv& ws_env, const TtkRect& rect)
{
	MainWidget* self = MainWidget::NewLC(ws_env, rect);
	CleanupStack::Pop(self);
	return self;
}

MainWidget* MainWidget::NewLC(CSymTtkWsEnv& ws_env, const TtkRect& rect)
{
	MainWidget* self = new(ELeave) MainWidget(ws_env, rect);
	self->ConstructL();
	CleanupStack::PushL(self);
	return self;
}

MainWidget::MainWidget(CSymTtkWsEnv& ws_env, const TtkRect& rect)
		: TtkWidget(ws_env, rect)
{
}

void MainWidget::ConstructL()
{
	TtkWidget::ConstructL(NULL);
	TtkRect rect(rect());
	rect.resize(-100, -100);
	rect.move(50, 50);
	component_ = NumberedWidget::NewL(ws_env(), rect, 3, &window());
}

void MainWidget::handle_key_event(TKeyEvent& key_event)
{
	TtkRect rect(component_->rect());
	TRect sym_rect;
	switch (key_event.iCode) {
	case EKeyUpArrow:
		rect.move(0, -10);
		component_->set_rect(rect);
		rect.resize(0, 10);
		sym_rect = TRect(rect.tl_.x_, rect.tl_.y_,
				 rect.br_.x_, rect.br_.y_);
		window().Window().Invalidate(sym_rect);
		break;
	case EKeyDownArrow:
		rect.move(0, 10);
		component_->set_rect(rect);
		rect.move(0, -10);
		rect.resize(0, 10);
		sym_rect = TRect(rect.tl_.x_, rect.tl_.y_,
				 rect.br_.x_, rect.br_.y_);
		window().Window().Invalidate(sym_rect);
		break;
	default:
		break;
	}
}

void MainWidget::handle_redraw_event(const TtkRect& rect)
{
	TtkWidget::handle_redraw_event(rect);
	component_->handle_redraw_event(rect);
}
