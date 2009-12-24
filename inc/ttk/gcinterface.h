/**
 * \file
 * \brief TtkGcInterface类声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_GCINTERFACE_H
#define TTK_GCINTERFACE_H

#include "ttk/common/color.h" /* TtkColor */

class TtkRect;
class TtkPoint;

/**
 * \brief 图形上下文接口
 *
 * 图形上下文保存当前的绘制环境，包括绘制的对象窗口、颜色、字体等。图形上下文中
 * 包含若干绘制图形元素的函数，例如绘制位图、文字、矩形等。
 */
class TtkGcInterface {
public:
	virtual ~TtkGcInterface() {}
public:
	virtual void clear(const TtkRect& rect) = 0;
	virtual void draw_line(const TtkPoint& p1, const TtkPoint& p2) = 0;
	virtual void draw_rect(const TtkRect& rect) = 0;
	virtual void draw_text(const char* text, const TtkRect& rect,
			       bool underline) = 0;
	virtual void draw_bitmap(const TtkBitmapInterface& bitmap,
				 const TtkRect& rect) = 0;
	virtual void set_clipping_rect(const TtkRect& rect) = 0;
	virtual void set_pen_color(TtkColor color) = 0;
	virtual void set_brush_color(TtkColor color) = 0;
};

#endif /* TTK_GCINTERFACE_H */
