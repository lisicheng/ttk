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

public: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& redraw_rect);
	bool focusable() const;
	void set_focus(bool has_focus);
	void set_rect(const TtkRect& new_rect);

public: /* new functions */
	void set_num_items(int num);
	int num_items() const;
	void set_items(TtkWidget** items);
	void set_focus_index(int index);
	int focus_index() const;
	
private: /* date members */
	int num_items_;
	TtkWidget** items_;
	int focus_index_;
	TtkWidget* scrollbar_;
};

#endif /* TTK_LIST_H */
