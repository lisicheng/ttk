#include "ui/label.h"

~TtkLabel::TtkLabel()
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
}

bool TtkLabel::focusable() const
{
	if (action_)
		return true;
	else
		return false;
}
