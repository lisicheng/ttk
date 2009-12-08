#include "framework/appui.h"
#include <uikon.hrh>
#include "ui/examplewsclient.h"

CAppUi::~CAppUi()
{
	delete iClient;
	delete iRoot;
}

void CAppUi::ConstructL()
{
	BaseConstructL();
	iClient = CWsClient::NewL();
	iRoot = CMainWidget::NewL(*iClient, ApplicationRect(), KRgbWhite);
}

void CAppUi::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EEikCmdExit: 
		Exit();
		break;
	}
}
