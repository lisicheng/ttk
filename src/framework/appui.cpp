#include "framework/appui.h"
#include <uikon.hrh>
#include "ui/examplewsclient.h"

void CAppUi::ConstructL()
{
	BaseConstructL();
	iClient = CExampleWsClient::NewL(ClientRect());
}

CAppUi::~CAppUi()
{
	delete iClient;
}

void CAppUi::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EEikCmdExit: 
		Exit();
		break;
	}
}
