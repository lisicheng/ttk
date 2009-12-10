#include "ui/numberedwidget.h"

#include "symttk/wsenv.h"
#include "common.h"

_LIT(KString0, "0");
_LIT(KString1, "1");
_LIT(KString2, "2");
_LIT(KString3, "3");
_LIT(KString4, "4");

CNumberedWidget::~CNumberedWidget()
{
}

CNumberedWidget* CNumberedWidget::NewL(CWsClient& aWsEnv, const TRect& aRect,
				       TInt aNum, CWindow* aParent)
{
	CNumberedWidget* self = CNumberedWidget::NewLC(aWsEnv, aRect, aNum,
						       aParent);
	CleanupStack::Pop(self);
	return self;
}

CNumberedWidget* CNumberedWidget::NewLC(CWsClient& aWsEnv, const TRect& aRect,
					TInt aNum, CWindow* aParent)
{
	CNumberedWidget* self = new(ELeave) CNumberedWidget(aWsEnv, aRect,
							    aNum);
	CleanupStack::PushL(self);
	self->ConstructL(aParent);
	return self;
}

/**
 * Redraws the contents of CNumberedWidget within a given
 * rectangle. CNumberedWidget displays a number in the window.
 */
void CNumberedWidget::Draw(const TRect& aRect)
{
	LOG("num:draw");
	LOGNUM(Rect().iTl.iX);
	LOGNUM(Rect().iTl.iY);
	LOGNUM(Rect().iBr.iX);
	LOGNUM(Rect().iBr.iY);
	CWindowGc& gc = WsEnv().Gc();
	gc.SetClippingRect(aRect);
	gc.Clear(aRect);

	LOG("num:draw:1");
	_LIT(KFontName, "Swiss");
	const TInt KFontHeight = 200;
	TFontSpec fontSpec(KFontName, KFontHeight);
	CFont* font;
	User::LeaveIfError(WsEnv().Screen().GetNearestFontInTwips(font,
								  fontSpec));
	TInt ascent = font->AscentInPixels();
	TInt descent = font->DescentInPixels();
	// vertical text offset
	TInt offset = (Rect().Size().iHeight + ascent - descent) / 2;
	LOG("num:draw:2");

	const TBufC<1> strings[5] = {*&KString0, *&KString1, *&KString2, *&KString3, *&KString4};

 	gc.SetPenColor(KRgbBlack);
	LOG("num:draw:3");
	gc.UseFont(font);
	LOG("num:draw:4");
	gc.DrawText(strings[iNum], Rect(), offset, CGraphicsContext::ECenter);
	LOG("num:draw:5");
	gc.DrawLine(Rect().iTl, Rect().iBr);
	LOG("num:draw:6");
	gc.DiscardFont();
	LOG("num:draw:7");

	WsEnv().Screen().ReleaseFont(font);
	LOG("num:draw:8");
}

CNumberedWidget::CNumberedWidget(CWsClient& aWsEnv, const TRect& aRect,
				 TInt aNum)
		: CWidget(aWsEnv, aRect), iNum(aNum)
{
}
