#include "ui/label.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"

TtkLabel::~TtkLabel()
{
}

TtkLabel::TtkLabel(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		   TtkWidget* parent, const char* text,
		   void (*action)())
		: TtkWidget(ws_env, rect, parent), text_(text), action_(action)
{
}

void TtkLabel::handle_key_event(TtkKeyEvent& key_event)
{
	if (key_event == kTtkKeyOk) {
		if (action_)
			action_();
	}
}

void TtkLabel::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(redraw_rect);

	TtkRect label_rect(rect());
	TtkRect text_rect(label_rect.tl_.x_ + 1,
			  label_rect.tl_.y_ + 1,
			  label_rect.br_.x_ - 1,
			  label_rect.br_.y_ - 1);
	gc.clear(label_rect);
	if (action_ || !action_) {	//for test
		gc.set_pen_color(kTtkColorBlue);
		if (has_focus())
			gc.draw_rect(label_rect);
		gc.draw_text(text_, text_rect, true);
	} else {
		gc.set_pen_color(kTtkColorBlack);
		gc.draw_text(text_, text_rect, false);
	}
}

bool TtkLabel::focusable() const
{
	if (action_)
		return true;
	else
		return false;
}

void TtkLabel::set_focus(bool has_focus)
{
	TtkWidget::set_focus(has_focus);
}
