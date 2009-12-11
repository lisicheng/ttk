#ifndef TTK_RECT_H
#define TTK_RECT_H

#include "ttk/common/point.h" /* TtkPoint */

class TtkRect {
public:
	TtkRect(int x1, int y1, int x2, int y2);
	TtkRect(const TtkPoint& tl, const TtkPoint& br);
public:
	void move(int dx, int dy);
	void move(const TtkPoint& offset);
	void resize(int dx, int dy);
	void bounding_rect(const TtkRect& rect);
	bool is_empty() const;
	bool intersects(const TtkRect& rect) const;
	void intersection(const TtkRect& hect);
	void normalize();
	bool contains(const TtkPoint& point) const;
	int width() const;
	int height() const;
	bool is_normalized() const;
	TtkPoint center() const;
	void set_width(int width);
	void set_height(int height);
public:
	TtkPoint tl_;
	TtkPoint br_;
};

#endif /* TTK_RECT_H */
