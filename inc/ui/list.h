#ifndef TTK_LIST_H
#define TTK_LIST_H

#include "e32def.h"
#include "ttk/widget.h"

class TtkWsEnvInterface;
class TtkWindowInterface;

#define K_EXPANDERS_NUM 100

/**
 * \brief 列表
 *
 * 列表包含竖向的若干列表项并在需要时显示滚动条\ref TtkScrollbar。每次滚动的距离
 * 由相应列表项的高度决定，以保证每次按键滚动一个列表项。
 */
class TtkList : public TtkWidget {
public:
	virtual ~TtkList();
	TtkList(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
			TtkWindowInterface* window);
	
public: /*from TtkWidget*/
	void handle_redraw_event(const TtkRect& rect);
	void handle_key_event(TtkKeyEvent& key_event);
	void set_focus(bool has_focus);
	bool focusable() const;
	void refresh_rect(const TtkRect& rect1, const TtkRect& rect2);
	
public:
	void set_iExpandersNum(int num);
	int get_iExpandersNum() const;
	
	void set_iExpanders(TtkWidget** expanders);
	
	void set_iFocusedNum(int num);
	int get_iFocusedNum() const;
	
private:
	int num_items_;
	TtkWidget** items_;
	int focus_index_;
	
	TtkWidget* scrollbar_;
};

#endif // TTK_LIST_H
