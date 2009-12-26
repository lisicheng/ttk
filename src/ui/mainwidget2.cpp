/*
 * mainwidget2.cpp
 *
 *  Created on: 2009-12-15
 *      Author: u
 */

#include "ui/mainwidget2.h"

#include "ttk/common.h"
#include "ttk/common/pointerevent.h"
#include "ttk/windowinterface.h"
#include "ui/list.h"
#include "ui/expander.h"
#include "ui/label.h"

MainWidget2::~MainWidget2()
{
	delete iList;
	iList = NULL;
}

MainWidget2::MainWidget2(TtkWsEnvInterface& ws_env, const TtkRect& rect)
		: TtkWidget(ws_env, rect, NULL)
{
	TtkList* list = new TtkList(ws_env, rect, &window());
	TtkExpander** expanders = new TtkExpander*[5];
	TtkRect expander_rect(rect.tl_.x_, rect.tl_.y_, rect.br_.x_, rect.tl_.y_+50);
	for(TInt i = 0; i < 5; ++i)
		{
		expanders[i] = new TtkExpander(ws_env, expander_rect, &window());
		TtkLabel* label = new TtkLabel(ws_env, expander_rect, &window(), "Label", NULL);
		expanders[i]->set_iLabel(label);
		expander_rect.move(0, 50);
		}
	list->set_iExpanders((TtkWidget**)expanders);
	list->set_iExpandersNum(5);
	list->set_iFocusedNum(0);
	list->set_focus(true);
	iList = list;
}

void MainWidget2::handle_key_event(TtkKeyEvent& key_event)
{
	switch(key_event){
	case kTtkKeyUp:
	case kTtkKeyDown:
	case kTtkKeyOk:
		iList->handle_key_event(key_event);
		break;
	default:
		break;
	}
}

void MainWidget2::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkWidget::handle_redraw_event(redraw_rect);
	iList->handle_redraw_event(redraw_rect);
}
