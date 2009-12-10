#include "ui/numberedwidget.h"

#include "symttk/wsenv.h"
#include "common.h"

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
	CWindowGc& gc = ws_env().Gc();
	TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
		       rect.br_.x_, rect.br_.y_);
	gc.SetClippingRect(sym_rect);
	gc.Clear(sym_rect);
 	gc.SetPenColor(KRgbBlack);
	TPoint tl(this->rect().tl_.x_, this->rect().tl_.y_);
	TPoint br(this->rect().br_.x_, this->rect().br_.y_);
	gc.DrawLine(tl, br);
}

NumberedWidget::NumberedWidget(CSymTtkWsEnv& ws_env, const TtkRect& rect,
				 int num)
		: TtkWidget(ws_env, rect), num_(num)
{
}
