#ifndef TTK_EXPANDER_H
#define TTK_EXPANDER_H

#include "ttk/widget.h"

class TtkWsEnvInterface;
class TtkWindowInterface;

/**
 * \brief 折叠页
 *
 * 折叠页可以打开或关闭，包含一个标题栏和一个可隐藏的客户区。标题栏中包含一个说明
 * 标签\ref TtkLabel和一个标示当前折叠状态的图片\ref TtkImage。
 */
class TtkExpander : public TtkWidget {
public:
	virtual ~TtkExpander();
	TtkExpander(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		    TtkWindowInterface* window, const char* text,
		    TtkWidget* contents);
public: /* from TtkWidget */
	void handle_redraw_event(const TtkRect& redraw_rect);
	void handle_key_event(TtkKeyEvent& key_event);
	void set_focus(bool has_focus);
	bool focusable() const;	
	void set_rect(const TtkRect& new_rect);
private:
	TtkLabel* label_;
	TtkImage* icon_;
	TtkWidget* contents_;
	bool expand_;
};

#endif /* TTK_EXPANDER_H */
