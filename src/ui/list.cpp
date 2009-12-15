#include "ui/list.h"

#include "ttk/gcinterface.h"
#include "ttk/wsenvinterface.h"
#include "ttk/windowinterface.h"

TtkList::~TtkList()
	{
	for(TInt i = 0; i < iExpandersNum; ++i)
		{
		delete iExpanders[i];
		iExpanders[i] = NULL;
		}
	}

TtkList::TtkList(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
		TtkWindowInterface* window):TtkWidget(ws_env, rect, window), iExpandersNum(0)
	{
	
	}

void TtkList::handle_redraw_event(const TtkRect& rect)
	{
	TtkWidget::handle_redraw_event(rect);
	for(TInt i = 0; i < iExpandersNum; ++i)
		iExpanders[i]->handle_redraw_event(iExpandersRects[i]);
	}

bool TtkList::add_iExpander(TtkWidget* expander)
	{
	if(iExpandersNum < K_EXPANDERS_NUM)
		{
		iExpanders[iExpandersNum] = expander;
		++iExpandersNum;
		return true;
		}
	return false;
	}
