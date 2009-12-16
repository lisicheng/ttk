#include "ui/expander.h"
#include "ttk/widget.h"

#include "ttk/common.h"
#include "ttk/common/color.h"
#include "ttk/gcinterface.h"
#include "ttk/windowinterface.h"
#include "ttk/wsenvinterface.h"

TtkExpander::~TtkExpander()
{
	if(iLabel){
		delete iLabel;
		iLabel = NULL;
	}
}

TtkExpander::TtkExpander(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
		TtkWindowInterface* window) : TtkWidget(ws_env, rect, window), iLabel(NULL)
{
}

void TtkExpander::handle_redraw_event(const TtkRect& rect)
{
	TtkGcInterface& gc = ws_env().gc();
	if(has_focus())
		gc.set_brush_color(kTtkColorRed);
	else
		gc.set_brush_color(kTtkColorGreen);
	gc.clear(rect);
	if(iLabel)
		iLabel->handle_redraw_event(iLabel->rect());
}

void TtkExpander::set_iLabel(TtkWidget* label)
{
	iLabel = label;
}
void TtkExpander::set_focus(bool has_focus)
{
	TtkWidget::set_focus(has_focus);
	iLabel->set_focus(has_focus);
}
void TtkExpander::handle_key_event(TtkKeyEvent& key_event)
{
	switch(key_event)
	{
	case kTtkKeyOk:
		if(rect().height() == iLabel->rect().height()){
			TtkRect rect_1_1 = rect();
			rect_1_1.resize(0, 100);
			set_rect(rect_1_1);
		}
		else {
			set_rect(iLabel->rect());
		}
		break;
	default:
		break;
	}
}
bool TtkExpander::focusable() const
{
	return true;
}
void TtkExpander::refresh_rect(const TtkRect& rect1, const TtkRect& rect2)
{
	int x = rect2.tl_.x_ - rect1.tl_.x_;
	int y = rect2.tl_.y_ - rect1.tl_.y_;
	int widthInc = rect2.width() - rect1.width();
	
	if(iLabel){
		TtkRect rect_1_1 = iLabel->rect();
		TtkRect rect_1_2 = rect_1_1;
		rect_1_2.move(x,y);
		iLabel->set_rect(rect_1_2);
		iLabel->refresh_rect(rect_1_1, iLabel->rect());
	}
}
