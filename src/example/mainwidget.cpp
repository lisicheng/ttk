#include "example/mainwidget.h"

#include "ttk/common.h"
#include "ttk/common/pointerevent.h"
#include "ttk/windowinterface.h"
#include "example/numberedwidget.h"
#include "ui/label.h"

MainWidget::~MainWidget()
{
	delete component_;
	delete text_;
}

MainWidget::MainWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect)
		: TtkWidget(ws_env, rect, NULL)
{
	TtkRect component_rect(rect.tl_.x_ + 50, rect.tl_.y_ + 50,
			       rect.br_.x_ - 50, rect.br_.y_ - 50);
	component_ = new NumberedWidget(ws_env, component_rect, 3, this);
	text_ = new TtkLabel(ws_env, TtkRect(10, 10, 100, 50), this, "abc好好", NULL);
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

void MainWidget::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkWidget::handle_redraw_event(redraw_rect);
	component_->handle_redraw_event(redraw_rect);
	text_->handle_redraw_event(redraw_rect);
}
