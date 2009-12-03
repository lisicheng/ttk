#include "framework/appui.h"
#include <uikon.hrh>
#include "ui/examplewsclient.h"

CAppUi::~CAppUi()
{
	delete iClient;
}

void CAppUi::ConstructL()
{
	BaseConstructL();
	iClient = CExampleWsClient::NewL(ApplicationRect());
}

void CAppUi::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EEikCmdExit: 
		Exit();
		break;
	}
}
