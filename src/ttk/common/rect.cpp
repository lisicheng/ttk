#include "ttk/common/rect.h"

TtkRect::TtkRect(int x1, int y1, int x2, int y2) : tl_(x1, y1), br_(x2, y2)
{
}

void TtkRect::move(int dx, int dy)
{
	tl_.x_ += dx;
	tl_.y_ += dy;

	br_.x_ += dx;
	br_.y_ += dy;
}

void TtkRect::resize(int dx, int dy)
{
	br_.x_ += dx;
	br_.y_ += dy;
}

int TtkRect::width() const
{
	return br_.x_ - tl_.x_;
}

int TtkRect::height() const
{
	return br_.y_ - tl_.y_;
}
