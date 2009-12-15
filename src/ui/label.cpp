#include "ui/label.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"

TtkLabel::~TtkLabel()
{
}

TtkLabel::TtkLabel(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		   TtkWindowInterface* window, const char* text,
		   void (*action)())
		: TtkWidget(ws_env, rect, window), text_(text), action_(action)
{
}

void TtkLabel::handle_key_event(TtkKeyEvent& key_event)
{
	if (key_event == kTtkKeyOk) {
		if (action_)
			action_();
	}
}

void TtkLabel::handle_redraw_event(const TtkRect& rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(rect);
	gc.clear(rect);
	if (action_) {
		gc.set_pen_color(kTtkColorBlue);
		gc.draw_text(text_, rect, true);
	} else {
		gc.set_pen_color(kTtkColorBlack);
		gc.draw_text(text_, rect, false);
	}
}

bool TtkLabel::focusable() const
{
	if (action_)
		return true;
	else
		return false;
}
