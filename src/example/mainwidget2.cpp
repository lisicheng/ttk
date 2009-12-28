#include "example/mainwidget2.h"

#include "ttk/common.h"
#include "ttk/common/pointerevent.h"
#include "ttk/windowinterface.h"
#include "ui/list.h"
#include "ui/expander.h"
#include "ui/label.h"

MainWidget2::~MainWidget2()
{
	delete list_;
}

MainWidget2::MainWidget2(TtkWsEnvInterface& ws_env, const TtkRect& rect)
	: TtkWidget(ws_env, rect, NULL)
{
	list_ = new TtkList(ws_env, rect, &window());
	TtkExpander** items = new TtkExpander*[5];
	TtkRect expander_rect(rect.tl_.x_, rect.tl_.y_, rect.br_.x_, rect.tl_.y_+50);
	for(TInt i = 0; i < 5; ++i) {
		items[i] = new TtkExpander(ws_env, expander_rect, &window(), "Label");
		expander_rect.move(0, 50);
	}
	list_->set_items((TtkWidget**)items);
	list_->set_num_items(5);
	list_->set_focus_index(0);
	list_->set_focus(true);
}

void MainWidget2::handle_key_event(TtkKeyEvent& key_event)
{
	switch(key_event){
	case kTtkKeyUp:
	case kTtkKeyDown:
	case kTtkKeyOk:
		list_->handle_key_event(key_event);
		break;
	default:
		break;
	}
}

void MainWidget2::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkWidget::handle_redraw_event(redraw_rect);
	list_->handle_redraw_event(redraw_rect);
}
