/**
 * \file
 * \brief TtkWidget类声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_WIDGET_H
#define TTK_WIDGET_H

#include "ttk/common/keyevent.h" /* TtkKeyEvent */
#include "ttk/common/rect.h" /* TtkRect */

class TtkPointerEvent;
class TtkWindowInterface;
class TtkWsEnvInterface;

/**
 * \brief 控件
 *
 * 此类为所有控件的父类，其中主要定义了处理三种事件的响应函数。构造控件时，传入
 * 绑定的窗口，如果为空，则创建一个新的窗口。此类包含基本的焦点功能。
 */
class TtkWidget
{
public:
	virtual ~TtkWidget();
	TtkWidget(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		  TtkWidget* parent);
public: /* virtual functions */
	virtual void handle_key_event(TtkKeyEvent& key_event);
	virtual void handle_pointer_event(TtkPointerEvent& pointer_event);
	virtual void handle_redraw_event(const TtkRect& redraw_rect);
	virtual bool focusable() const;
	virtual void set_focus(bool has_focus);
	virtual void set_rect(const TtkRect& new_rect);
public: /* non-virtual functions */
	bool has_focus() const;
	TtkWsEnvInterface& ws_env();
	const TtkRect& rect() const;
protected:
	TtkWindowInterface& window() const;
private:
	TtkWsEnvInterface& ws_env_;
	TtkRect rect_;
	TtkWindowInterface* window_;
	bool own_window_;
	bool has_focus_;
};

#endif /* TTK_WIDGET_H */
