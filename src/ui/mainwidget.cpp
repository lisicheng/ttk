#include "ui/mainwidget.h"

#include "ui/numberedwidget.h"

CMainWidget::~CMainWidget()
{
	delete iComponent;
}

CMainWidget* CMainWidget::NewL(CWsClient& aWsEnv, const TRect& aRect)
{
	CMainWidget* self = CMainWidget::NewLC(aWsEnv, aRect);
	CleanupStack::Pop(self);
	return self;
}

CMainWidget* CMainWidget::NewLC(CWsClient& aWsEnv, const TRect& aRect)
{
	CMainWidget* self = new(ELeave) CMainWidget(aWsEnv, aRect);
	self->ConstructL();
	CleanupStack::PushL(self);
	return self;
}

CMainWidget::CMainWidget(CWsClient& aWsEnv, const TRect& aRect)
		: CWidget(aWsEnv, aRect)
{
}

void CMainWidget::ConstructL()
{
	CWidget::ConstructL(NULL);
	TRect rect(Rect());
	rect.Resize(-100, -100);
	rect.Move(50, 50);
	iComponent = CNumberedWidget::NewL(WsEnv(), rect, 3, &Window());
}

void CMainWidget::HandleKeyEventL(TKeyEvent& aKeyEvent)
{
}

void CMainWidget::Draw(const TRect& aRect)
{
	CWidget::Draw(aRect);
	iComponent->Draw(aRect);
}
