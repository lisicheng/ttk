#include "ui/mainwindow.h"

CMainWindow* CMainWindow::NewL(CWsClient& aClient, const TRect& aRect,
			       const TRgb& aColor, CWindow* aParent = 0)
{
	CMainWindow* self = CMainWindow::NewLC(aClient, aRect, aColor, aParent);
	CleanupStack::Pop(self);
	return self;
}

CMainWindow* CMainWindow::NewLC(CWsClient& aClient, const TRect& aRect,
			        const TRgb& aColor, CWindow* aParent = 0)
{
	CMainWindow* self = new(ELeave) CMainWindow(aClient);
	CleanupStack::PushL(self);
	self->ConstructL(aRect, aColor, aParent);
	return self;
}

/**
 * Redraws the contents of CMainWindow within a given rectangle.
 */
void CMainWindow::Draw(const TRect& aRect)
{
	CWindowGc* gc = SystemGc();
	gc->SetClippingRect(aRect);
	gc->Clear(aRect);
}

/**
 * Handles pointer events for CMainWindow.
 */
void CMainWindow::HandlePointerEvent (TPointerEvent& aPointerEvent)
{	
	switch (aPointerEvent.iType) {
	case TPointerEvent::EButton1Down:
	case TPointerEvent::EButton1Up:
		break;
	default:
		break;
	}
}

CMainWindow::CMainWindow(CWsClient& aClient) : CWindow(aClient)
{
}

