/**
 * \file
 * \brief TtkScrollbar类定义
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#include "ui/scrollbar.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"
#include "ttk/windowinterface.h"

TtkScrollbar::~TtkScrollbar()
{
}

TtkScrollbar::TtkScrollbar(TtkWsEnvInterface& ws_env, const TtkRect& rect,
			   TtkWindowInterface* window)
	: TtkWidget(ws_env, rect, window)
{
}

void TtkScrollbar::handle_redraw_event(const TtkRect& rect)
{
	TtkWidget::handle_redraw_event(rect);
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(rect);
	gc.clear(rect);
}
