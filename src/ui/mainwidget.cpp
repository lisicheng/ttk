#include "ui/mainwidget.h"

#include "ttk/common.h"
#include "ttk/common/pointerevent.h"
#include "ttk/windowinterface.h"
#include "ui/numberedwidget.h"

MainWidget::~MainWidget()
{
	delete component_;
}

MainWidget::MainWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect)
		: TtkWidget(ws_env, rect, NULL)
{
	TtkRect rect(rect);
	rect.resize(-100, -100);
	rect.move(50, 50);
	component_ = new NumberedWidget(ws_env, rect, 3, &window());
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
