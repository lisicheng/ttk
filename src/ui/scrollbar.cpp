/**
 * \file
 * \brief TtkScrollbar类定义
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
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

void TtkScrollbar::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(redraw_rect);
	gc.set_brush_color(kTtkColorWhite);
	gc.clear(redraw_rect);
	
	if(totalLength > 0){
		int x = rect().width();
		int y = rect().height();
		int barLength = scrollbarLength * y / totalLength;
		int barMove = startPoint * y / totalLength;
		TtkRect rect_draw(rect().tl_.x_, rect().tl_.y_, rect().tl_.x_+x, rect().tl_.y_+barLength);
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
