#ifndef TTK_LIST_H
#define TTK_LIST_H

#include "e32def.h"
#include "ttk/widget.h"

class TtkWsEnvInterface;
class TtkWindowInterface;

#define K_EXPANDERS_NUM 100

class TtkList : public TtkWidget {
public:
	virtual ~TtkList();
	TtkList(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
			TtkWindowInterface* window);
	
public:/*from TtkWidget*/
	void handle_redraw_event(const TtkRect& rect);
	
public:
	void set_iExpandersNum(TInt num);
	void set_iExpanders(TtkWidget** expanders);
	
private:
	TInt iExpandersNum;
	TtkWidget** iExpanders;
};

#endif // TTK_LIST_H
