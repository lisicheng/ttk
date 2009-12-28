#include "ui/list.h"

#include "ui/scrollbar.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"
#include "ttk/windowinterface.h"

TtkList::~TtkList()
{
	for (int i = 0; i < num_items_; ++i) {
		delete items_[i];
	}
	delete scrollbar_;
}

TtkList::TtkList(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
		TtkWindowInterface* window) : TtkWidget(ws_env, rect, window),
		num_items_(0), items_(NULL), focus_index_(0), scrollbar_(NULL)
{
}

void TtkList::handle_key_event(TtkKeyEvent& key_event)
{
	int dy;
	switch(key_event) {
	case kTtkKeyUp:
		if (focus_index_ <= 0)
			break;
		dy = items_[focus_index_-1]->rect().tl_.y_ - rect().tl_.y_;
		if (dy < 0) {
			for (int i = 0; i < num_items_; ++i) {
				TtkRect new_rect = items_[i]->rect();
				new_rect.move(0, -dy);
				items_[i]->set_rect(new_rect);
			}
			items_[focus_index_]->set_focus(false);
			--focus_index_;
			items_[focus_index_]->set_focus(true);
			window().redraw(rect());
		} else {
			items_[focus_index_]->set_focus(false);
			window().redraw(items_[focus_index_]->rect());
			--focus_index_;
			items_[focus_index_]->set_focus(true);
			window().redraw(items_[focus_index_]->rect());
		}
		break;
	case kTtkKeyDown:
		if (focus_index_ >= num_items_ -1)
			break;
		dy = items_[focus_index_+1]->rect().br_.y_ - rect().br_.y_;
		if (dy > 0) {
			int top_dy = items_[focus_index_+1]->rect().tl_.y_ -
				     rect().tl_.y_;
			if (top_dy < dy)
				dy = top_dy;
			for (int i = 0; i < num_items_; ++i) {
				TtkRect new_rect = items_[i]->rect();
				new_rect.move(0, -dy);
				items_[i]->set_rect(new_rect);
			}
			items_[focus_index_]->set_focus(false);
			++focus_index_;
			items_[focus_index_]->set_focus(true);
			window().redraw(rect());
		} else {
			items_[focus_index_]->set_focus(false);
			window().redraw(items_[focus_index_]->rect());
			++focus_index_;
			items_[focus_index_]->set_focus(true);
			window().redraw(items_[focus_index_]->rect());
		}
		break;
	case kTtkKeyOk:
		if (num_items_ <= 0)
			break;
		items_[focus_index_]->handle_key_event(key_event);
		if (focus_index_ < num_items_ -1) {
			int dy = items_[focus_index_]->rect().br_.y_ -
				 items_[focus_index_+1]->rect().tl_.y_;
			for (int i = focus_index_+1; i < num_items_; ++i) {
				TtkRect new_rect = items_[i]->rect();
				new_rect.move(0, dy);
				items_[i]->set_rect(new_rect);
			}
		}
		int dy = items_[focus_index_]->rect().br_.y_-rect().br_.y_;
		if (dy > 0) {
			int top_dy = items_[focus_index_]->rect().tl_.y_ -
				     rect().tl_.y_;
			if (top_dy < dy)
				dy = top_dy;
			for (int i = 0; i < num_items_; ++i) {
				TtkRect new_rect = items_[i]->rect();
				new_rect.move(0, -dy);
				items_[i]->set_rect(new_rect);
			}
		}
		window().redraw(rect()); /* simple & stupid */
		break;
	default:
		break;
	}
}

/* TODO: should complete ASAP. Set scrollbar in anothre function. */
void TtkList::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkWidget::handle_redraw_event(rect());
	if (num_items_ <= 0)
		return;
	int total_length = items_[num_items_-1]->rect().br_.y_ -
			   items_[0]->rect().tl_.y_;
	if (total_length > rect().height()) {
		if (!scrollbar_) {
			TtkRect scroll_rect(rect().br_.x_-10, rect().tl_.y_,
					    rect().br_.x_, rect().br_.y_);
			scrollbar_ = new TtkScrollbar(ws_env(), scroll_rect,
					 &window());
		}
		int scrollbarLength = rect().height();
		int startPoint = rect().tl_.y_ - items_[0]->rect().tl_.y_;
		TtkScrollbar* scrollbar = (TtkScrollbar*)scrollbar_;
		scrollbar->set_totalLength(total_length);
		scrollbar->set_scrollbarLength(scrollbarLength);
		scrollbar->set_startPoint(startPoint);
			
		//change items_'s rect
		for (int i = 0; i < num_items_; ++i) {
			if (items_[i]->rect().width() == rect().width()) {
				TtkRect new_rect = items_[i]->rect();
				new_rect.resize(-10, 0);
				items_[i]->set_rect(new_rect);
			}
		}

		//draw them
		for (int i = 0; i < num_items_; ++i)
			items_[i]->handle_redraw_event(items_[i]->rect());
		scrollbar_->handle_redraw_event(scrollbar_->rect());
	} else {
		for (int i = 0; i < num_items_; ++i) {
			if (items_[i]->rect().width() < rect().width()) {
				TtkRect new_rect = items_[i]->rect();
				new_rect.resize(10, 0);
				items_[i]->set_rect(new_rect);
			}
		}
		
		//draw them
		for (int i = 0; i < num_items_; ++i)
			items_[i]->handle_redraw_event(items_[i]->rect());
	}
}

bool TtkList::focusable() const
{
	if (num_items_ > 0)
		return true;
	else
		return false;
}

void TtkList::set_focus(bool has_focus)
{
	TtkWidget::set_focus(has_focus);
	items_[focus_index_]->set_focus(has_focus);
}

void TtkList::set_rect(const TtkRect& new_rect)
{
	int top_dx = new_rect.tl_.x_ - rect().tl_.x_;
	int top_dy = new_rect.tl_.y_ - rect().tl_.y_;
	int d_width = new_rect.width() - rect().width();
	for (int i = 0; i < num_items_; ++i) {
		TtkRect new_rect = items_[i]->rect();
		new_rect.move(top_dx, top_dy);
		new_rect.resize(d_width, 0);
		items_[i]->set_rect(new_rect);
	}
	if (scrollbar_) {
		TtkRect new_rect = scrollbar_->rect();
		new_rect.move(top_dx + d_width, top_dy);
		scrollbar_->set_rect(new_rect);
	}
}

void TtkList::set_num_items(int num)
{
	num_items_ = num;
}

int TtkList::num_items() const
{
	return num_items_;
}

void TtkList::set_items(TtkWidget** items)
{
	items_ = items;
}

void TtkList::set_focus_index(int index)
{
	focus_index_ = index;
}

int TtkList::focus_index() const
{
	return focus_index_;
}
