#include "ui/numberedwidget.h"

#include "symttk/wsenv.h"
#include "common.h"

_LIT(KString0, "0");
_LIT(KString1, "1");
_LIT(KString2, "2");
_LIT(KString3, "3");
_LIT(KString4, "4");

NumberedWidget::~NumberedWidget()
{
}

NumberedWidget* NumberedWidget::NewL(CSymTtkWsEnv& ws_env, const TRect& rect,
				       TInt num, CSymTtkWindow* window)
{
	NumberedWidget* self = NumberedWidget::NewLC(ws_env, rect, num,
						       window);
	CleanupStack::Pop(self);
	return self;
}

NumberedWidget* NumberedWidget::NewLC(CSymTtkWsEnv& ws_env, const TRect& rect,
					TInt num, CSymTtkWindow* window)
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
void NumberedWidget::handle_redraw_event(const TRect& rect)
{
	CWindowGc& gc = ws_env().Gc();
	gc.SetClippingRect(rect);
	gc.Clear(rect);

	_LIT(KFontName, "Swiss");
	const TInt KFontHeight = 200;
	TFontSpec fontSpec(KFontName, KFontHeight);
	CFont* font;
	User::LeaveIfError(ws_env().Screen().GetNearestFontInTwips(font,
								  fontSpec));
	TInt ascent = font->AscentInPixels();
	TInt descent = font->DescentInPixels();
	// vertical text offset
	TInt offset = (this->rect().Size().iHeight + ascent - descent) / 2;

	const TBufC<1> strings[5] = {*&KString0, *&KString1, *&KString2, *&KString3, *&KString4};
 	gc.SetPenColor(KRgbBlack);
	gc.UseFont(font);
	gc.DrawText(strings[num_], this->rect(), offset, CGraphicsContext::ECenter);
	gc.DrawLine(this->rect().iTl, this->rect().iBr);
	gc.DiscardFont();

	ws_env().Screen().ReleaseFont(font);
}

NumberedWidget::NumberedWidget(CSymTtkWsEnv& ws_env, const TRect& rect,
				 TInt num)
		: TtkWidget(ws_env, rect), num_(num)
{
}
