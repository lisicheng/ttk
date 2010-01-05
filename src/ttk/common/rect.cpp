#include "ttk/common/rect.h"

TtkRect::TtkRect(int x1, int y1, int x2, int y2) : tl_(x1, y1), br_(x2, y2)
{
}

TtkRect::TtkRect(const TtkPoint& tl, const TtkPoint& br) : tl_(tl), br_(br)
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

void TtkRect::intersection(const TtkRect& rect)
{
	if (tl_.x_ < rect.tl_.x_) tl_.x_ = rect.tl_.x_;
	if (br_.x_ > rect.br_.x_) br_.x_ = rect.br_.x_;
	if (tl_.y_ < rect.tl_.y_) tl_.y_ = rect.tl_.y_;
	if (br_.y_ > rect.br_.y_) br_.y_ = rect.br_.y_;
	if (!intersects(rect)) {
		br_.x_ = tl_.x_;
		br_.y_ = tl_.y_;
	}
}

bool TtkRect::intersects(const TtkRect& rect) const
{
	if (tl_.x_ < rect.br_.x_ && rect.tl_.x_ < br_.x_ &&
	    tl_.y_ < rect.br_.y_ && rect.tl_.y_ < br_.y_)
		return true;
	else
		return false;
}

