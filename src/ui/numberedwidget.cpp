#include "ui/numberedwidget.h"
#include "window/wsclient.h"
#include "common.h"

_LIT(KString0, "0");
_LIT(KString1, "1");
_LIT(KString2, "2");
_LIT(KString3, "3");
_LIT(KString4, "4");

CNumberedWidget::~CNumberedWidget()
{
}

CNumberedWidget* CNumberedWidget::NewL(CWsClient& aWsEnv,
					const CWindow* aParent,
					const TRect& aRect, TInt aNum)
{
	CNumberedWidget* self = CNumberedWidget::NewLC(aWsEnv, aParent, aRect,
						       aNum);
	CleanupStack::Pop(self);
	return self;
}

CNumberedWidget* CNumberedWidget::NewLC(CWsClient& aWsEnv,
					const CWindow* aParent,
					const TRect& aRect, TInt aNum)
{
	CNumberedWidget* self = new(ELeave) CNumberedWidget(aWsEnv, aNum);
	CleanupStack::PushL(self);
	self->ConstructL(aParent, aRect);
	return self;
}

/**
 * Redraws the contents of CNumberedWidget within a given
 * rectangle. CNumberedWidget displays a number in the window.
 */
void CNumberedWidget::Draw(const TRect& aRect)
{
	LOG("Num:Draw");
	CWindowGc& gc = WsEnv().Gc();
	gc.SetClippingRect(aRect);
	gc.Clear(aRect);

	_LIT(KFontName, "Swiss");
	const TInt KFontHeight = 200;
	TFontSpec fontSpec(KFontName, KFontHeight);
	CFont* font;
	User::LeaveIfError(WsEnv().Screen().GetNearestFontInTwips(font,
								  fontSpec));
	TSize size = Rect().Size();
	TInt ascent = font->AscentInPixels();
	TInt descent = font->DescentInPixels();
	// vertical text offset
	TInt offset = (size.iHeight + ascent - descent) / 2;

	const TBufC<1> strings[5] = {*&KString0, *&KString1, *&KString2, *&KString3, *&KString4};

 	gc.SetPenColor(KRgbBlack);
	gc.UseFont(font);
	gc.DrawText(strings[iNumber], TRect(size), offset,
		    CGraphicsContext::ECenter);
	gc.DrawLine(Rect().iTl, size.AsPoint());
	gc.DiscardFont();
	WsEnv().Screen().ReleaseFont(font);
}

CNumberedWidget::CNumberedWidget(CWsClient& aWsEnv, TInt aNum)
	: CWidget(aWsEnv), iNumber(aNum)
{
}
