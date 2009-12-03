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
	iClient = CExampleWsClient::NewL(ClientRect());
}

void CAppUi::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EEikCmdExit: 
		Exit();
		break;
	}
}
