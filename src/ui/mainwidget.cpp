#include "ui/mainwidget.h"

CMainWidget::~CMainWidget()
{
	delete iComponent;
}

CMainWidget::HandleKeyEventL(TKeyEvent& aKeyEvent);
{
}

CMainWidget::ConstructL(const CWidget* aParent, const TRect& aRect)
{
	CWidget::ConstructL(aParent, aRect);
	TRect rect(aRect);
	rect.Resize(-50, -50);
	iComponent = CNumberedWidget::NewL(iWsEnv, this, rect, 3);
}
