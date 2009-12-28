#include "example/numberedwidget.h"

#include "ttk/common/color.h"
#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"

NumberedWidget::~NumberedWidget()
{
}

NumberedWidget::NumberedWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect,
			       int num, TtkWindowInterface* window)
		: TtkWidget(ws_env, rect, window), num_(num)
{
}

/**
 * Redraws the contents of NumberedWidget within a given
 * rectangle. NumberedWidget displays a number in the window.
 */
void NumberedWidget::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(redraw_rect);
	gc.clear(rect());
 	gc.set_pen_color(kTtkColorBlack);
 	gc.set_brush_color(kTtkColorGreen);
	gc.draw_rect(rect());
	gc.draw_line(rect().tl_, rect().br_);
}
