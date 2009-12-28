/**
 * \file
 * \brief TtkScrollbar类声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_SCROLLBAR_H
#define TTK_SCROLLBAR_H

#include "ttk/widget.h" /* TtkWidget */

class TtkWsEnvInterface;
class TtkWindowInterface;

/**
 * \brief 滚动条
 */
class TtkScrollbar : public TtkWidget {
public:
	virtual ~TtkScrollbar();
	TtkScrollbar(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		     TtkWindowInterface* window);
	
public: /* from TtkWidget */
	void handle_redraw_event(const TtkRect& rect);

};

#endif /* TTK_SCROLLBAR_H */
