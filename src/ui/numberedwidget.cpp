#include "ui/numberedwidget.h"

_LIT(KString0, "0");
_LIT(KString1, "1");
_LIT(KString2, "2");
_LIT(KString3, "3");
_LIT(KString4, "4");

CNumberedWidget* CNumberedWidget::NewL(CWsClient& aWsEnv,
					const CWidget* aParent,
					const TRect* aRect, TInt aNum)
{
	CNumberedWidget* self = CNumberedWidget::NewLC(aWsEnv, aParent, aRect,
						       aNum);
	CleanupStack::Pop(self);
	return self;
}

CNumberedWidget* CNumberedWidget::NewLC(CWsClient& aWsEnv,
					const CWidget* aParent,
					const TRect* aRect, TInt aNum)
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
	CWindowGc& gc = WsEnv().Gc();
	gc.SetClippingRect(aRect);
	gc.Clear(aRect);

	TSize size = Window().Size();
	TInt ascent = Font().AscentInPixels();
	TInt descent = Font().DescentInPixels();
	// vertical text offset
	TInt offset = (size.iHeight + ascent - descent) / 2;

	const TBufC<1> strings[5] = {*&KString0, *&KString1, *&KString2, *&KString3, *&KString4};

 	gc.SetPenColor(KRgbBlack);
	gc.UseFont(&Font());
	gc.DrawText(strings[iNumber], TRect(size), offset,
		    CGraphicsContext::ECenter);
	gc.DrawLine(TPoint(), TPoint(size));
	gc.DiscardFont();
}

CNumberedWidget::CNumberedWidget(CWsClient& aWsEnv, TInt aNum)
	: CWidget(aWsEnv), iNumber(aNum)
{
}
