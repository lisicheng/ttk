#include "window/widget.h"
#include "window/wsclient.h"
#include "window/wsredrawer.h"

CWidget::~CWidget()
{
}

void CWidget::ConstructMainWindowL()
{
}

CWidget::CWidget(CWsClient& aWsEnv) : iWsEnv(aWsEnv)
{
}

void CWidget::ConstructL()
{
	ConstructMainWindowL();
}
