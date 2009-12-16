#include "ui/scrollbar.h"

#include "ttk/common/color.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"
#include "ttk/windowinterface.h"

TtkScrollbar::~TtkScrollbar()
{
}

TtkScrollbar::TtkScrollbar(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		TtkWindowInterface* window): TtkWidget(ws_env, rect, window), totalLength(0),
		scrollbarLength(0), startPoint(0)
{
}

void TtkScrollbar::handle_redraw_event(const TtkRect& rect)
{
	TtkWidget::handle_redraw_event(rect);
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(rect);
	gc.clear(rect);
	
	if(totalLength > 0){
		int x = this->rect().width();
		int y = this->rect().height();
		int barLength = scrollbarLength * y / totalLength;
		int barMove = startPoint * y / totalLength;
		TtkRect rect_draw(this->rect().tl_.x_, this->rect().tl_.y_, this->rect().tl_.x_+x, this->rect().tl_.y_+barLength);
		rect_draw.move(0, barMove);
		gc.set_brush_color(kTtkColorBlack);
		gc.draw_rect(rect_draw);
	}
}

void TtkScrollbar::set_totalLength(int length)
{
	totalLength = length;
}
void TtkScrollbar::set_scrollbarLength(int sLength)
{
	scrollbarLength = sLength;
}
void TtkScrollbar::set_startPoint(int sPoint)
{
	startPoint = sPoint;
}
