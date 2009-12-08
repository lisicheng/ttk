#include "ui/mainwidget.h"
#include "ui/numberedwidget.h"
#include "common.h"

CMainWidget::~CMainWidget()
{
	delete iComponent;
}

CMainWidget* CMainWidget::NewL(CWsClient& aWsEnv, const CWindow* aParent,
			       const TRect& aRect)
{
	CMainWidget* self = CMainWidget::NewLC(aWsEnv, aParent, aRect);
	CleanupStack::Pop(self);
	return self;
}

CMainWidget* CMainWidget::NewLC(CWsClient& aWsEnv, const CWindow* aParent,
				const TRect& aRect)
{
	CMainWidget* self = new(ELeave) CMainWidget(aWsEnv, aRect);
	self->ConstructL(aParent);
	CleanupStack::PushL(self);
	return self;
}

void CMainWidget::HandleKeyEventL(TKeyEvent& aKeyEvent)
{
}

void CMainWidget::Draw(const TRect& aRect)
{
	LOG("main:draw");
	CWidget::Draw(aRect);
	iComponent->Draw(aRect);
}

CMainWidget::CMainWidget(CWsClient& aWsEnv, const TRect& aRect)
		: CWidget(aWsEnv, aRect)
{
}

void CMainWidget::ConstructL(const CWindow* aParent)
{
	CWidget::ConstructL(aParent);
	TRect rect(Rect());
	rect.Resize(-50, -50);
	iComponent = CNumberedWidget::NewL(WsEnv(), rect, 3, &Window());
}
