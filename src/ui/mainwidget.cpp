#include "ui/mainwidget.h"
#include "ui/numberedwidget.h"

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
	CMainWidget* self = new(ELeave) CMainWidget(aWsEnv);
	self->ConstructL(aParent, aRect);
	CleanupStack::PushL(self);
	return self;
}

void CMainWidget::HandleKeyEventL(TKeyEvent& aKeyEvent)
{
}

CMainWidget::CMainWidget(CWsClient& aWsEnv) : CWidget(aWsEnv)
{
}

void CMainWidget::ConstructL(const CWindow* aParent, const TRect& aRect)
{
	CWidget::ConstructL(aParent, aRect);
	TRect rect(aRect);
	rect.Resize(-50, -50);
	iComponent = CNumberedWidget::NewL(WsEnv(), &Window(), rect, 3);
}
