#ifndef TTK_LABEL_H
#define TTK_LABEL_H

#include "ttk/widget.h" /* TtkWidget */

/**
 * \brief 标签
 *
 * 文本标签包括单行文本。构造时指定文本内容和可选的关联动作。如果指定了关联动作，
 * 则标签可以获取焦点，文字加下划线。获得焦点时，显示虚线边框，响应按键事件执行
 * 关联动作。
 */
class TtkLabel : public TtkWidget {
public:
	virtual ~TtkLabel();
	TtkLabel(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		 TtkWidget* parent, const char* text,
		 void (*action)());
public: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& redraw_rect);
	void set_focus(bool has_focus);
	bool focusable() const;
private:
	const char* text_;
	void (*action_)();
};

#endif /* TTK_LABEL_H */
