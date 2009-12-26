#ifndef TTK_SCROLLBAR_H
#define TTK_SCROLLBAR_H

#include "ttk/widget.h"

class TtkWsEnvInterface;
class TtkWindowInterface;

/**
 * \brief 滚动条
 */
class TtkScrollbar : public TtkWidget {
public:
	virtual ~TtkScrollbar();
	TtkScrollbar(TtkWsEnvInterface& ws_env, const TtkRect& rect, TtkWindowInterface* window);
	
public:/*from TtkWidget*/
	void handle_redraw_event(const TtkRect& redraw_rect);
	
public:
	void set_totalLength(int length);
	void set_scrollbarLength(int sLength);
	void set_startPoint(int sPoint);
	
private:/*data*/
	int totalLength;
	int scrollbarLength;
	int startPoint;
};

#endif // TTK_SCROLLBAR_H
