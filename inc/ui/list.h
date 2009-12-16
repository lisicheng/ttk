#ifndef TTK_LIST_H
#define TTK_LIST_H

#include "e32def.h"
#include "ttk/widget.h"

class TtkWsEnvInterface;
class TtkWindowInterface;

class TtkList : public TtkWidget {
public:
	virtual ~TtkList();
	TtkList(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
			TtkWindowInterface* window);
	
public:/*from TtkWidget*/
	void handle_redraw_event(const TtkRect& rect);
	void handle_key_event(TtkKeyEvent& key_event);
	void set_focus(bool has_focus);
	bool focusable() const;
	void refresh_rect(const TtkRect& rect1, const TtkRect& rect2);
	
public:
	void set_iExpandersNum(TInt num);
	TInt get_iExpandersNum() const;
	
	void set_iExpanders(TtkWidget** expanders);
	
	void set_iFocusedNum(TInt num);
	TInt get_iFocusedNum() const;
	
private:
	TInt iExpandersNum;
	TtkWidget** iExpanders;
	TInt iFocusedNum;
	
	TtkWidget* iScrollbar;
};

#endif // TTK_LIST_H
