#include "ttk/widget.h"

#include "symttk/window.h"
#include "symttk/wsenv.h"

CWidget::~CWidget()
{
	if (iOwnWindow)
		delete iWindow;
}

CWidget* CWidget::NewL(CWsClient& aWsEnv, const TRect& aRect, CWindow* aWindow)
{
	CWidget* self = CWidget::NewLC(aWsEnv, aRect, aWindow);
	CleanupStack::Pop(self);
	return self;
}

CWidget* CWidget::NewLC(CWsClient& aWsEnv, const TRect& aRect, CWindow* aWindow)
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

void CWidget::HandlePointerEventL(TPointerEvent& aPointerEvent)
{
	return;
}

void CWidget::Draw(const TRect& aRect)
{
	CWindowGc& gc = WsEnv().Gc();
	gc.Clear(aRect);
}

CWsClient& CWidget::WsEnv()
{
	return iWsEnv;
}

const TRect& CWidget::Rect() const
{
	return iRect;
}

void CWidget::SetRect(const TRect& aRect)
{
	iRect = aRect;
}

CWidget::CWidget(CWsClient& aWsEnv, const TRect& aRect)
		: iWsEnv(aWsEnv), iRect(aRect)
{
}

void CWidget::ConstructL(CWindow* aWindow)
{
	if (aWindow) {
		iWindow = aWindow;
		iOwnWindow = EFalse;
	} else {
		iWindow = CWindow::NewL(*this, KRgbWhite);
		iOwnWindow = ETrue;
	}
}

CWindow& CWidget::Window() const
{
	return *iWindow;
}
