#include "ui/expander.h"
#include "ttk/widget.h"

#include "ttk/common.h"
#include "ttk/common/color.h"
#include "ttk/gcinterface.h"
#include "ttk/windowinterface.h"
#include "ttk/wsenvinterface.h"

TtkExpander::~TtkExpander()
{
	delete label_;
}

TtkExpander::TtkExpander(TtkWsEnvInterface& ws_env, const TtkRect& rect,
			 TtkWindowInterface* window)
	: TtkWidget(ws_env, rect, window), label_(NULL)
{
}

void TtkExpander::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(redraw_rect);
	if (has_focus())
		gc.set_brush_color(kTtkColorRed);
	else
		gc.set_brush_color(kTtkColorGreen);
	gc.clear(rect());
	if (label_)
		label_->handle_redraw_event(label_->rect());
}

void TtkExpander::set_iLabel(TtkWidget* label)
{
	label_ = label;
}

void TtkExpander::set_focus(bool has_focus)
{
	TtkWidget::set_focus(has_focus);
	label_->set_focus(has_focus);
}

void TtkExpander::handle_key_event(TtkKeyEvent& key_event)
{
	switch(key_event) {
	case kTtkKeyOk:
		if (rect().height() == label_->rect().height()) {
			TtkRect rect_1_1 = rect();
			rect_1_1.resize(0, 100);
			set_rect(rect_1_1);
		} else {
			set_rect(label_->rect());
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
	
	if (label_) {
		TtkRect rect_1_1 = label_->rect();
		TtkRect rect_1_2 = rect_1_1;
		rect_1_2.move(x,y);
		label_->set_rect(rect_1_2);
		label_->refresh_rect(rect_1_1, label_->rect());
	}
}
