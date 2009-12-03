#include "ui/numberedwindow.h"

_LIT(KString1,"1");
_LIT(KString2,"2");
_LIT(KString3,"3");
_LIT(KString4,"4");
_LIT(KString5,"5");

CNumberedWindow* CNumberedWindow::NewL(CWsClient* aClient, TInt aNum,
				       const TRect& aRect, const TRgb& aColor,
				       CWindow* aParent = 0)
{
	CNumberedWindow* self = CNumberedWindow::NewLC(aClient, aNum, aRect,
						       aColor, aParent);
	CleanupStack::Pop(self);
	return self;
}

CNumberedWindow* CNumberedWindow::NewLC(CWsClient* aClient, TInt aNum,
					const TRect& aRect, const TRgb& aColor,
					CWindow* aParent = 0)
{
	CNumberedWindow* self = new(ELeave) CNumberedWindow(aClient, aNum);
	CleanupStack::PushL(aClient);
	self->ConstructL(aRect, aColor, aParent);
	return self;
}

/****************************************************************************\
|	Function:	CNumberedWindow::Draw
|	Purpose:	Redraws the contents of CNumberedWindow within a given
|				rectangle.  CNumberedWindow displays a number in the window.
|	Input:		aRect	Rectangle that needs redrawing
|	Output:		None
\****************************************************************************/
void CNumberedWindow::Draw(const TRect& aRect)
{
	const TBufC<1> strings[5] = {*&KString1, *&KString2, *&KString3, *&KString4, *&KString5};

	CWindowGc* gc=SystemGc(); // get a graphics context
	gc->SetClippingRect(aRect); // clip outside the redraw area
	gc->Clear(aRect); // clear the redraw area
	TSize size = Window().Size();
	TInt height=size.iHeight; // Need window height to calculate vertical text offset
	TInt ascent = Font()->AscentInPixels();
	TInt descent = Font()->DescentInPixels();
	TInt offset = (height + (ascent + descent)) / 2; // Calculate vertical text offset
 	gc->SetPenColor(TRgb(0,0,0)); // Set pen to black
	gc->UseFont(Font());
	gc->DrawText(strings[iNumber], TRect(TPoint(0,0) + iOffset, size), offset,
													CGraphicsContext::ECenter);
	gc->DrawLine(TPoint(0,0) + iOffset, TPoint(size.iWidth, height) + iOffset);
	gc->DiscardFont();
}

/****************************************************************************\
|	Function:	CNumberedWindow::HandlePointerEvent
|	Purpose:	Handles pointer events for CNumberedWindow.
|	Input:		aPointerEvent	The pointer event
|	Output:		None
\****************************************************************************/
void CNumberedWindow::HandlePointerEvent (TPointerEvent& aPointerEvent)
{	
	switch (aPointerEvent.iType) {
	case TPointerEvent::EButton1Down:
		Window().Scroll(TPoint(0,-2));
		iOffset += TPoint(0,-2);
		iRepeatRect.iTl = aPointerEvent.iPosition - TPoint(10,10);
		iRepeatRect.iBr = aPointerEvent.iPosition + TPoint(10,10);
		iScrollDir = Up;
		Window().RequestPointerRepeatEvent(TTimeIntervalMicroSeconds32 (20000), iRepeatRect);
		break;
	case TPointerEvent::EButtonRepeat:
		if (iScrollDir == Up) {
			Window().Scroll(TPoint(0,-2));
			iOffset += TPoint(0,-2);
		} else {
			Window().Scroll(TPoint(0,2));
			iOffset += TPoint(0,2);
		}
		Window().RequestPointerRepeatEvent(TTimeIntervalMicroSeconds32 (20000), iRepeatRect);
		break;
	case TPointerEvent::EButton3Down:
		Window().Scroll(TPoint(0,2));
		iOffset += TPoint(0,2);
		iRepeatRect.iTl = aPointerEvent.iPosition - TPoint(10,10);
		iRepeatRect.iBr = aPointerEvent.iPosition + TPoint(10,10);
		iScrollDir = Down;
		Window().RequestPointerRepeatEvent(TTimeIntervalMicroSeconds32 (100000), iRepeatRect);
		break;
	default:
		break;
	}
}

/****************************************************************************\
|	Function:	Constructor/Destructor for CNumberedWindow
|	Input:		aClient		Client application that owns the window
\****************************************************************************/
CNumberedWindow::CNumberedWindow(CWsClient* aClient, TInt aNum)
	: CWindow(aClient), iNumber(aNum),
	  iOldPos(0, 0), iOffset(0, 0), iRepeatRect(0, 0, 0, 0)
{
}

