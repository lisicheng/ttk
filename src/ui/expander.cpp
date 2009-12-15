#include "ui/expander.h"

#include "ttk/common.h"
#include "ttk/gcinterface.h"
#include "ttk/windowinterface.h"
#include "ttk/wsenvinterface.h"

TtkExpander::~TtkExpander()
	{
	if(iLabel)
		{
		delete iLabel;
		iLabel = NULL;
		}
	}

TtkExpander::TtkExpander(TtkWsEnvInterface& ws_env, const TtkRect& rect, 
		TtkWindowInterface* window) : TtkWidget(ws_env, rect, window), iLabel(NULL)
	{
	}

void TtkExpander::handle_redraw_event(const TtkRect& rect)
	{
	TtkWidget::handle_redraw_event(rect);
	if(iLabel)
		iLabel->handle_redraw_event(iLabel->rect());
	}

void TtkExpander::set_iLabel(TtkWidget* label)
	{
	iLabel = label;
	}
