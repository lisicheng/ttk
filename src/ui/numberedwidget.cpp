#include "ui/numberedwidget.h"

#include "common.h"
#include "symttk/gc.h"
#include "symttk/wsenv.h"
#include "ttk/common/color.h"

/*
_LIT(KString0, "0");
_LIT(KString1, "1");
_LIT(KString2, "2");
_LIT(KString3, "3");
_LIT(KString4, "4");
*/

NumberedWidget::~NumberedWidget()
{
}

NumberedWidget* NumberedWidget::NewL(CSymTtkWsEnv& ws_env, const TtkRect& rect,
				       int num, CSymTtkWindow* window)
{
	NumberedWidget* self = NumberedWidget::NewLC(ws_env, rect, num,
						       window);
	CleanupStack::Pop(self);
	return self;
}

NumberedWidget* NumberedWidget::NewLC(CSymTtkWsEnv& ws_env, const TtkRect& rect,
					int num, CSymTtkWindow* window)
{
	NumberedWidget* self = new(ELeave) NumberedWidget(ws_env, rect,
							    num);
	CleanupStack::PushL(self);
	self->ConstructL(window);
	return self;
}

/**
 * Redraws the contents of NumberedWidget within a given
 * rectangle. NumberedWidget displays a number in the window.
 */
void NumberedWidget::handle_redraw_event(const TtkRect& rect)
{
	TtkGcInterface& gc = ws_env().Gc();
	gc.set_clipping_rect(rect);
	gc.clear(rect);
 	gc.set_pen_color(kTtkColorBlack);
	gc.draw_line(this->rect().tl_, this->rect().br_);
}

NumberedWidget::NumberedWidget(CSymTtkWsEnv& ws_env, const TtkRect& rect,
				 int num)
		: TtkWidget(ws_env, rect), num_(num)
{
}
