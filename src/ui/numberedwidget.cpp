#include "ui/numberedwidget.h"

#include "common.h"
#include "symttk/gc.h"
#include "symttk/wsenv.h"
#include "ttk/common/color.h"

/*
_LIT(KString0, "0");
_LIT(KString1, "1");
_LIT(KString2, "2");
_LIT(KString3, "3");
_LIT(KString4, "4");
*/

NumberedWidget::~NumberedWidget()
{
}

NumberedWidget* NumberedWidget::NewL(TtkWsEnvInterface& ws_env, const TtkRect& rect,
				       int num, TtkWindowInterface* window)
{
	NumberedWidget* self = new NumberedWidget(ws_env, rect, num, window);
	return self;
}

/**
 * Redraws the contents of NumberedWidget within a given
 * rectangle. NumberedWidget displays a number in the window.
 */
void NumberedWidget::handle_redraw_event(const TtkRect& rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(rect);
	gc.clear(rect);
 	gc.set_pen_color(kTtkColorBlack);
	gc.draw_line(this->rect().tl_, this->rect().br_);
}

NumberedWidget::NumberedWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect,
				 int num, TtkWindowInterface* window)
		: TtkWidget(ws_env, rect, window), num_(num)
{
}
