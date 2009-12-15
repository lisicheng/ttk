#ifndef TTK_EXPANDER_H
#define TTK_EXPANDER_H

#include "ttk/widget.h"

class TtkWsEnvInterface;
class TtkWindowInterface;

class TtkExpander : public TtkWidget {
public:
	virtual ~TtkExpander();
	TtkExpander(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
			TtkWindowInterface* window);
	
public:/*from TtkWidget*/
	void handle_redraw_event(const TtkRect& rect);
	
public:
	void set_iLabel(TtkWidget* label);
	
private:
	TtkWidget* iLabel;
};

#endif // TTK_EXPANDER_H
