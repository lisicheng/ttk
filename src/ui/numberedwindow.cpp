#include "ui/numberedwindow.h"

_LIT(KString0, "0");
_LIT(KString1, "1");
_LIT(KString2, "2");
_LIT(KString3, "3");
_LIT(KString4, "4");

CNumberedWindow* CNumberedWindow::NewL(CWsClient& aClient, TInt aNum,
				       const TRect& aRect, const TRgb& aColor,
				       CWindow* aParent = 0)
{
	CNumberedWindow* self = CNumberedWindow::NewLC(aClient, aNum, aRect,
						       aColor, aParent);
	CleanupStack::Pop(self);
	return self;
}

CNumberedWindow* CNumberedWindow::NewLC(CWsClient& aClient, TInt aNum,
					const TRect& aRect, const TRgb& aColor,
					CWindow* aParent = 0)
{
	CNumberedWindow* self = new(ELeave) CNumberedWindow(aClient, aNum);
	CleanupStack::PushL(self);
	self->ConstructL(aRect, aColor, aParent);
	return self;
}

/**
 * Redraws the contents of CNumberedWindow within a given
 * rectangle. CNumberedWindow displays a number in the window.
 */
void CNumberedWindow::Draw(const TRect& aRect)
{
	CWindowGc& gc = SystemGc();
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
	gc.DrawText(strings[iNumber], TRect(iOffset, size), offset,
		    CGraphicsContext::ECenter);
	gc.DrawLine(iOffset, iOffset + size);
	gc.DiscardFont();
}

void CNumberedWindow::HandlePointerEvent(TPointerEvent& /*aPointerEvent*/)
{	
}

void CNumberedWindow::ScrollUpL()
{	
	Window().Scroll(TPoint(0, -2));
	iOffset += TPoint(0, -2);
}

void CNumberedWindow::ScrollDownL()
{	
	Window().Scroll(TPoint(0, 2));
	iOffset += TPoint(0, 2);
}

CNumberedWindow::CNumberedWindow(CWsClient& aClient, TInt aNum)
	: CWindow(aClient), iNumber(aNum)
{
}
