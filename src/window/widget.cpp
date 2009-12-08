#include "window/widget.h"

#include "window/wsclient.h"
#include "window/window.h"
#include "window/wsredrawer.h"

CWidget::~CWidget()
{
	if (iOwnWindow)
		delete iWindow;
}

CWidget* CWidget::NewL(CWsClient& aWsEnv, const TRect& aRect,
		       const CWindow* aWindow)
{
	CWidget* self = CWidget::NewLC(aWsEnv, aRect, aWindow);
	CleanupStack::Pop(self);
	return self;
}

CWidget* CWidget::NewLC(CWsClient& aWsEnv, const TRect& aRect,
			const CWindow* aWindow)
{
	CWidget* self = new(ELeave) CWidget(aWsEnv, aRect);
	CleanupStack::PushL(self);
	self->ConstructL(aWindow);
	return self;
}

void CWidget::HandleKeyEventL(TKeyEvent& aKeyEvent)
{
	return;
}

void CWidget::Draw(const TRect& aRect)
{
	CWindowGc& gc = WsEnv().Gc();
	gc.Clear(aRect);
}

const TRect& CWidget::Rect() const
{
	return iRect;
}

CWidget::CWidget(CWsClient& aWsEnv, const TRect& aRect)
		: iWsEnv(aWsEnv), iRect(aRect)
{
}

void CWidget::ConstructL(const CWindow* aWindow)
{
	if (aWindow) {
		iWindow = aWindow;
		iOwnWindow = EFalse;
	} else {
		iWindow = CWindow::NewL(iWsEnv, *this, KRgbWhite);
		iOwnWindow = ETrue;
	}
}

CWsClient& CWidget::WsEnv()
{
	return iWsEnv;
}

void CWidget::SetRect(TRect& aRect)
{
	iRect = aRect;
}

const CWindow& CWidget::Window() const
{
	return *iWindow;
}
