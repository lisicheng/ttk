#include "ui/list.h"

#include "ui/scrollbar.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"
#include "ttk/windowinterface.h"

TtkList::~TtkList()
{
	for (TInt i = 0; i < iExpandersNum; ++i){
		delete iExpanders[i];
		iExpanders[i] = NULL;
	}
	delete iScrollbar;
	iScrollbar = NULL;
}

TtkList::TtkList(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
		TtkWindowInterface* window) : TtkWidget(ws_env, rect, window),
		iExpandersNum(0), iExpanders(NULL),iFocusedNum(0),iScrollbar(NULL)
{
}

void TtkList::handle_redraw_event(const TtkRect& rect)
{
	TtkWidget::handle_redraw_event(rect);
	if(iExpandersNum > 0){
		if(iExpanders[iExpandersNum-1]->rect().br_.y_-iExpanders[0]->rect().tl_.y_ >
			this->rect().height()){
			if(iScrollbar == NULL){
				TtkRect scrollRect(this->rect().width()-10, this->rect().tl_.y_, this->rect().width(), this->rect().br_.y_);
				iScrollbar = new TtkScrollbar(ws_env(), scrollRect, &window());
			}
			int totalLength = iExpanders[iExpandersNum-1]->rect().br_.y_-iExpanders[0]->rect().tl_.y_;
			int scrollbarLength = this->rect().height();
			int startPoint = this->rect().tl_.y_ - iExpanders[0]->rect().tl_.y_;
			TtkScrollbar* scrollbar = (TtkScrollbar*)iScrollbar;
			scrollbar->set_totalLength(totalLength);
			scrollbar->set_scrollbarLength(scrollbarLength);
			scrollbar->set_startPoint(startPoint);
			
			//change iExpanders' rect
			for (int i = 0; i < iExpandersNum; ++i){
				if(iExpanders[i]->rect().width() == this->rect().width()){
					TtkRect rect_1_1 = iExpanders[i]->rect();
					TtkRect rect_1_2 = rect_1_1;
					rect_1_2.resize(-10, 0);
					iExpanders[i]->set_rect(rect_1_2);
					iExpanders[i]->refresh_rect(rect_1_1, iExpanders[i]->rect());
				}
			}
			
			//draw them
			for(int i = 0; i < iExpandersNum; ++i)
				iExpanders[i]->handle_redraw_event(iExpanders[i]->rect());
			iScrollbar->handle_redraw_event(iScrollbar->rect());
		}
		else {
			for (int i = 0; i < iExpandersNum; ++i){
				if(iExpanders[i]->rect().width() < this->rect().width()){
					TtkRect rect_1_1 = iExpanders[i]->rect();
					TtkRect rect_1_2 = rect_1_1;
					rect_1_2.resize(10, 0);
					iExpanders[i]->set_rect(rect_1_2);
					iExpanders[i]->refresh_rect(rect_1_1, iExpanders[i]->rect());
				}
			}
			
			//draw them
			for (int i = 0; i < iExpandersNum; ++i)
				iExpanders[i]->handle_redraw_event(iExpanders[i]->rect());
		}
	}
}

void TtkList::set_iExpandersNum(TInt num)
{
	iExpandersNum = num;
}
TInt TtkList::get_iExpandersNum() const
{
	return iExpandersNum;
}

void TtkList::set_iExpanders(TtkWidget** expanders)
{
	iExpanders = expanders;
}
void TtkList::set_iFocusedNum(TInt num)
{
	iFocusedNum = num;
}
TInt TtkList::get_iFocusedNum() const
{
	return iFocusedNum;
}

void TtkList::set_focus(bool has_focus)
{
	TtkWidget::set_focus(has_focus);
	iExpanders[iFocusedNum]->set_focus(has_focus);
}
void TtkList::handle_key_event(TtkKeyEvent& key_event)
{
	switch(key_event)
	{
		case kTtkKeyUp:
			if(iFocusedNum > 0){
				if(iExpanders[iFocusedNum-1]->rect().tl_.y_ < rect().tl_.y_){
					//redraw all the list rect area
					int moveY = iExpanders[iFocusedNum-1]->rect().tl_.y_ - rect().tl_.y_;
					for (int i = 0; i < iExpandersNum; ++i){
						TtkRect rect_1_1 = iExpanders[i]->rect();
						TtkRect rect_1_2 = rect_1_1;
						rect_1_2.move(0, -moveY);
						iExpanders[i]->set_rect(rect_1_2);
						iExpanders[i]->refresh_rect(rect_1_1, iExpanders[i]->rect());
					}
					set_focus(false);
					--iFocusedNum;
					set_focus(true);
					window().redraw(rect());
				}
				else {
					set_focus(false);
					window().redraw(iExpanders[iFocusedNum]->rect());
					--iFocusedNum;
					set_focus(true);
					window().redraw(iExpanders[iFocusedNum]->rect());
				}
			}
			break;
		case kTtkKeyDown:
			if(iFocusedNum < iExpandersNum -1){
				if(iExpanders[iFocusedNum+1]->rect().br_.y_ > rect().br_.y_){
					int moveY1 = iExpanders[iFocusedNum+1]->rect().tl_.y_-rect().tl_.y_;
					int moveY2 = iExpanders[iFocusedNum+1]->rect().br_.y_-rect().br_.y_;
					int moveY3 = (moveY1 < moveY2)? moveY1 : moveY2;
					for (int i = 0; i < iExpandersNum; ++i){
						TtkRect rect_1_1 = iExpanders[i]->rect();
						TtkRect rect_1_2 = rect_1_1;
						rect_1_2.move(0, -moveY3);
						iExpanders[i]->set_rect(rect_1_2);
						iExpanders[i]->refresh_rect(rect_1_1, iExpanders[i]->rect());
					}
					set_focus(false);
					++iFocusedNum;
					set_focus(true);
					window().redraw(rect());
				}
				else {
					set_focus(false);
					window().redraw(iExpanders[iFocusedNum]->rect());
					++iFocusedNum;
					set_focus(true);
					window().redraw(iExpanders[iFocusedNum]->rect());
				}
			}
			break;
		case kTtkKeyOk:
			if(iExpandersNum <= 0)
				break;
			iExpanders[iFocusedNum]->handle_key_event(key_event);//wrap or unwrap, reset rect
			if(iFocusedNum < iExpandersNum -1){
				int moveY = iExpanders[iFocusedNum]->rect().br_.y_ - iExpanders[iFocusedNum+1]->rect().tl_.y_;
				for(int i = iFocusedNum+1; i < iFocusedNum; ++i){
					TtkRect rect_1_1 = iExpanders[i]->rect();
					TtkRect rect_1_2 = rect_1_1;
					rect_1_2.move(0, moveY);					
					iExpanders[i]->set_rect(rect_1_2);
					iExpanders[i]->refresh_rect(rect_1_1, iExpanders[i]->rect());
				}
			}
			if(iExpanders[iFocusedNum]->rect().br_.y_ > rect().br_.y_){
				int moveY1 = iExpanders[iFocusedNum+1]->rect().tl_.y_-rect().tl_.y_;
				int moveY2 = iExpanders[iFocusedNum+1]->rect().br_.y_-rect().br_.y_;
				int moveY3 = (moveY1 < moveY2)? moveY1 : moveY2;
				for (int i = 0; i < iExpandersNum; ++i){
					TtkRect rect_1_1 = iExpanders[i]->rect();
					TtkRect rect_1_2 = rect_1_1;
					rect_1_2.move(0, -moveY3);
					iExpanders[i]->set_rect(rect_1_2);
					iExpanders[i]->refresh_rect(rect_1_1, iExpanders[i]->rect());
				}
				set_focus(false);
				++iFocusedNum;
				set_focus(true);
				window().redraw(rect());
			}
			else {
				TtkRect rect(iExpanders[iFocusedNum]->rect().tl_, this->rect().br_);
				window().redraw(rect);
			}
			break;
		default:
			break;
	}
}
bool TtkList::focusable() const
{
	if(iExpandersNum > 0)
		return true;
	else
		return false;
}

void TtkList::refresh_rect(const TtkRect& rect1, const TtkRect& rect2)
{
	int x = rect2.tl_.x_ - rect1.tl_.x_;
	int y = rect2.tl_.y_ - rect1.tl_.y_;
	int widthInc = rect2.width() - rect1.width();
	for(int i = 0; i < iExpandersNum; ++i){
		TtkRect rect_1_1 = iExpanders[i]->rect();
		TtkRect rect_1_2 = rect_1_1;
		rect_1_2.move(x,y);
		rect_1_2.resize(widthInc, 0);
		iExpanders[i]->set_rect(rect_1_2);
		iExpanders[i]->refresh_rect(rect_1_1, iExpanders[i]->rect());
		
	}
	if(iScrollbar){
		TtkRect rect_1_1 = iScrollbar->rect();
		TtkRect rect_1_2 = rect_1_1;
		rect_1_2.move(x,y);
		iScrollbar->set_rect(rect_1_2);
		iScrollbar->refresh_rect(rect_1_1, iScrollbar->rect());
	}
}
