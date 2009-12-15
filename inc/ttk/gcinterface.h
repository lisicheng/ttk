#ifndef TTK_GCINTERFACE_H
#define TTK_GCINTERFACE_H

#include "ttk/common/color.h" /* TtkColor */

class TtkRect;
class TtkPoint;

class TtkGcInterface {
public:
	virtual ~TtkGcInterface() {}
public:
	virtual void clear(const TtkRect& rect) = 0;
	virtual void draw_line(const TtkPoint& p1, const TtkPoint& p2) = 0;
	virtual void draw_rect(const TtkRect& rect) = 0;
	virtual void draw_text(const char* text, const TtkRect& rect,
			       bool underline) = 0;
	virtual void set_clipping_rect(const TtkRect& rect) = 0;
	virtual void set_pen_color(TtkColor color) = 0;
	virtual void set_brush_color(TtkColor color) = 0;
};

#endif /* TTK_GCINTERFACE_H */
