#include "ui/mainwidget.h"

#include "common.h"
#include "ui/numberedwidget.h"
#include "symttk/window.h"

CMainWidget::~CMainWidget()
{
	delete iComponent;
}

CMainWidget* CMainWidget::NewL(CSymTtkWsEnv& aWsEnv, const TRect& aRect)
{
	CMainWidget* self = CMainWidget::NewLC(aWsEnv, aRect);
	CleanupStack::Pop(self);
	return self;
}

CMainWidget* CMainWidget::NewLC(CSymTtkWsEnv& aWsEnv, const TRect& aRect)
{
	CMainWidget* self = new(ELeave) CMainWidget(aWsEnv, aRect);
	self->ConstructL();
	CleanupStack::PushL(self);
	return self;
}

CMainWidget::CMainWidget(CSymTtkWsEnv& aWsEnv, const TRect& aRect)
		: TtkWidget(aWsEnv, aRect)
{
}

void CMainWidget::ConstructL()
{
	TtkWidget::ConstructL(NULL);
	TRect rect(Rect());
	rect.Resize(-100, -100);
	rect.Move(50, 50);
	iComponent = CNumberedWidget::NewL(WsEnv(), rect, 3, &Window());
}

void CMainWidget::HandleKeyEventL(TKeyEvent& aKeyEvent)
{
	TRect rect(iComponent->Rect());
	switch (aKeyEvent.iCode) {
	case EKeyUpArrow:
		LOG("up");
		rect.Move(0, -10);
		iComponent->SetRect(rect);
		rect.Resize(0, 10);
		Window().Window().Invalidate(rect);
		break;
	case EKeyDownArrow:
		rect.Move(0, 10);
		iComponent->SetRect(rect);
		rect.Move(0, -10);
		rect.Resize(0, 10);
		Window().Window().Invalidate(rect);
		break;
	default:
		break;
	}
	LOG("end:handleKeyevent");
}

void CMainWidget::Draw(const TRect& aRect)
{
	LOG("draw");
	TtkWidget::Draw(aRect);
	iComponent->Draw(aRect);
}
