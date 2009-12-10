#include "ui/mainwidget.h"

#include "common.h"
#include "ui/numberedwidget.h"
#include "symttk/window.h"
#include "ttk/common/pointerevent.h"

MainWidget::~MainWidget()
{
	delete component_;
}

MainWidget* MainWidget::NewL(TtkWsEnvInterface& ws_env, const TtkRect& rect)
{
	MainWidget* self = new(ELeave) MainWidget(ws_env, rect);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
}

MainWidget::MainWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect)
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

void MainWidget::handle_key_event(TtkKeyEvent& key_event)
{
	TtkRect rect(component_->rect());
	switch (key_event) {
	case kTtkKeyUp:
		rect.move(0, -10);
		component_->set_rect(rect);
		rect.resize(0, 10);
		window().redraw(rect);
		break;
	case kTtkKeyDown:
		rect.move(0, 10);
		component_->set_rect(rect);
		rect.move(0, -10);
		rect.resize(0, 10);
		window().redraw(rect);
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
