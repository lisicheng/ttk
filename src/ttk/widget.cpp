#include "ttk/widget.h"

#include "symttk/window.h"
#include "symttk/wsenv.h"

TtkWidget::~TtkWidget()
{
	if (iOwnWindow)
		delete iWindow;
}

TtkWidget* TtkWidget::NewL(CSymTtkWsEnv& aWsEnv, const TRect& aRect, CSymTtkWindow* aWindow)
{
	TtkWidget* self = TtkWidget::NewLC(aWsEnv, aRect, aWindow);
	CleanupStack::Pop(self);
	return self;
}

TtkWidget* TtkWidget::NewLC(CSymTtkWsEnv& aWsEnv, const TRect& aRect, CSymTtkWindow* aWindow)
{
	TtkWidget* self = new(ELeave) TtkWidget(aWsEnv, aRect);
	CleanupStack::PushL(self);
	self->ConstructL(aWindow);
	return self;
}

void TtkWidget::HandleKeyEventL(TKeyEvent& aKeyEvent)
{
	return;
}

void TtkWidget::HandlePointerEventL(TPointerEvent& aPointerEvent)
{
	return;
}

void TtkWidget::Draw(const TRect& aRect)
{
	CWindowGc& gc = WsEnv().Gc();
	gc.Clear(aRect);
}

CSymTtkWsEnv& TtkWidget::WsEnv()
{
	return iWsEnv;
}

const TRect& TtkWidget::Rect() const
{
	return iRect;
}

void TtkWidget::SetRect(const TRect& aRect)
{
	iRect = aRect;
}

TtkWidget::TtkWidget(CSymTtkWsEnv& aWsEnv, const TRect& aRect)
		: iWsEnv(aWsEnv), iRect(aRect)
{
}

void TtkWidget::ConstructL(CSymTtkWindow* aWindow)
{
	if (aWindow) {
		iWindow = aWindow;
		iOwnWindow = EFalse;
	} else {
		iWindow = CSymTtkWindow::NewL(*this, KRgbWhite);
		iOwnWindow = ETrue;
	}
}

CSymTtkWindow& TtkWidget::Window() const
{
	return *iWindow;
}
