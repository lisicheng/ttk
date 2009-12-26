#include "ui/list.h"

#include "ui/scrollbar.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"
#include "ttk/windowinterface.h"

TtkList::~TtkList()
{
	for (int i = 0; i < num_items_; ++i) {
		delete items_[i];
		items_[i] = NULL;
	}
	delete scrollbar_;
	scrollbar_ = NULL;
}

TtkList::TtkList(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
		TtkWindowInterface* window) : TtkWidget(ws_env, rect, window),
		num_items_(0), items_(NULL), focus_index_(0), scrollbar_(NULL)
{
}

void TtkList::handle_redraw_event(const TtkRect& rect)
{
	TtkWidget::handle_redraw_event(this->rect());
	if (num_items <= 0)
		return;
	if (items_[num_items_-1]->rect().br_.y_ - items_[0]->rect().tl_.y_ >
	    this->rect().height()) {
		if (!scrollbar_) {
			TtkRect scrollRect(this->rect().width()-10, this->rect().tl_.y_, this->rect().width(), this->rect().br_.y_);
			scrollbar_ = new TtkScrollbar(ws_env(), scrollRect, &window());
		}
		int totalLength = items_[num_items_-1]->rect().br_.y_-items_[0]->rect().tl_.y_;
		int scrollbarLength = this->rect().height();
		int startPoint = this->rect().tl_.y_ - items_[0]->rect().tl_.y_;
		TtkScrollbar* scrollbar = (TtkScrollbar*)scrollbar_;
		scrollbar->set_totalLength(totalLength);
		scrollbar->set_scrollbarLength(scrollbarLength);
		scrollbar->set_startPoint(startPoint);
			
		//change items_' rect
		for (int i = 0; i < num_items_; ++i) {
			if (items_[i]->rect().width() == this->rect().width()) {
				TtkRect rect_1_1 = items_[i]->rect();
				TtkRect rect_1_2 = rect_1_1;
				rect_1_2.resize(-10, 0);
				items_[i]->set_rect(rect_1_2);
				items_[i]->refresh_rect(rect_1_1, items_[i]->rect());
			}
		}
			
		//draw them
		for (int i = 0; i < num_items_; ++i)
			items_[i]->handle_redraw_event(items_[i]->rect());
		scrollbar_->handle_redraw_event(scrollbar_->rect());
	} else {
		for (int i = 0; i < num_items_; ++i) {
			if (items_[i]->rect().width() < this->rect().width()) {
				TtkRect rect_1_1 = items_[i]->rect();
				TtkRect rect_1_2 = rect_1_1;
				rect_1_2.resize(10, 0);
				items_[i]->set_rect(rect_1_2);
				items_[i]->refresh_rect(rect_1_1, items_[i]->rect());
			}
		}
		
		//draw them
		for (int i = 0; i < num_items_; ++i)
			items_[i]->handle_redraw_event(items_[i]->rect());
	}
}

void TtkList::set_iExpandersNum(int num)
{
	num_items_ = num;
}

int TtkList::get_iExpandersNum() const
{
	return num_items_;
}

void TtkList::set_iExpanders(TtkWidget** expanders)
{
	items_ = expanders;
}
void TtkList::set_iFocusedNum(int num)
{
	focus_index_ = num;
}
int TtkList::get_iFocusedNum() const
{
	return focus_index_;
}

void TtkList::set_focus(bool has_focus)
{
	TtkWidget::set_focus(has_focus);
	items_[focus_index_]->set_focus(has_focus);
}
void TtkList::handle_key_event(TtkKeyEvent& key_event)
{
	switch(key_event) {
	case kTtkKeyUp:
		if (focus_index_ > 0) {
			if (items_[focus_index_-1]->rect().tl_.y_ < rect().tl_.y_) {
				//redraw all the list rect area
				int moveY = items_[focus_index_-1]->rect().tl_.y_ - rect().tl_.y_;
				for (int i = 0; i < num_items_; ++i) {
					TtkRect rect_1_1 = items_[i]->rect();
					TtkRect rect_1_2 = rect_1_1;
					rect_1_2.move(0, -moveY);
					items_[i]->set_rect(rect_1_2);
					items_[i]->refresh_rect(rect_1_1, items_[i]->rect());
				}
				set_focus(false);
				--focus_index_;
				set_focus(true);
				window().redraw(rect());
			} else {
				set_focus(false);
				window().redraw(items_[focus_index_]->rect());
				--focus_index_;
				set_focus(true);
				window().redraw(items_[focus_index_]->rect());
			}
		}
		break;
	case kTtkKeyDown:
		if (focus_index_ < num_items_ -1) {
			if (items_[focus_index_+1]->rect().br_.y_ > rect().br_.y_) {
				int moveY1 = items_[focus_index_+1]->rect().tl_.y_-rect().tl_.y_;
				int moveY2 = items_[focus_index_+1]->rect().br_.y_-rect().br_.y_;
				int moveY3 = (moveY1 < moveY2)? moveY1 : moveY2;
				for (int i = 0; i < num_items_; ++i) {
					TtkRect rect_1_1 = items_[i]->rect();
					TtkRect rect_1_2 = rect_1_1;
					rect_1_2.move(0, -moveY3);
					items_[i]->set_rect(rect_1_2);
					items_[i]->refresh_rect(rect_1_1, items_[i]->rect());
				}
				set_focus(false);
				++focus_index_;
				set_focus(true);
				window().redraw(rect());
			} else {
				set_focus(false);
				window().redraw(items_[focus_index_]->rect());
				++focus_index_;
				set_focus(true);
				window().redraw(items_[focus_index_]->rect());
			}
		}
		break;
	case kTtkKeyOk:
		if (num_items_ <= 0)
			break;
		items_[focus_index_]->handle_key_event(key_event);//wrap or unwrap, reset rect
		if (focus_index_ < num_items_ -1) {
			int moveY = items_[focus_index_]->rect().br_.y_ - items_[focus_index_+1]->rect().tl_.y_;
			for (int i = focus_index_+1; i < num_items_; ++i) {
				TtkRect rect_1_1 = items_[i]->rect();
				TtkRect rect_1_2 = rect_1_1;
				rect_1_2.move(0, moveY);					
				items_[i]->set_rect(rect_1_2);
				items_[i]->refresh_rect(rect_1_1, items_[i]->rect());
			}
		}
		if (items_[focus_index_]->rect().br_.y_ > rect().br_.y_) {
			int moveY1 = items_[focus_index_]->rect().tl_.y_-rect().tl_.y_;
			int moveY2 = items_[focus_index_]->rect().br_.y_-rect().br_.y_;
			int moveY3 = (moveY1 < moveY2)? moveY1 : moveY2;
			for (int i = 0; i < num_items_; ++i) {
				TtkRect rect_1_1 = items_[i]->rect();
				TtkRect rect_1_2 = rect_1_1;
				rect_1_2.move(0, -moveY3);
				items_[i]->set_rect(rect_1_2);
				items_[i]->refresh_rect(rect_1_1, items_[i]->rect());
			}
		}
		window().redraw(rect());
		break;
	default:
		break;
	}
}
bool TtkList::focusable() const
{
	if (num_items_ > 0)
		return true;
	else
		return false;
}

void TtkList::refresh_rect(const TtkRect& rect1, const TtkRect& rect2)
{
	int x = rect2.tl_.x_ - rect1.tl_.x_;
	int y = rect2.tl_.y_ - rect1.tl_.y_;
	int widthInc = rect2.width() - rect1.width();
	for (int i = 0; i < num_items_; ++i) {
		TtkRect rect_1_1 = items_[i]->rect();
		TtkRect rect_1_2 = rect_1_1;
		rect_1_2.move(x, y);
		rect_1_2.resize(widthInc, 0);
		items_[i]->set_rect(rect_1_2);
		items_[i]->refresh_rect(rect_1_1, items_[i]->rect());
		
	}
	if (scrollbar_) {
		TtkRect rect_1_1 = scrollbar_->rect();
		TtkRect rect_1_2 = rect_1_1;
		rect_1_2.move(x, y);
		scrollbar_->set_rect(rect_1_2);
		scrollbar_->refresh_rect(rect_1_1, scrollbar_->rect());
	}
}
