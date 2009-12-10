#include "framework/appui.h"
#include <uikon.hrh>
#include "symttk/wsenv.h"
#include "ui/mainwidget.h"

CAppUi::~CAppUi()
{
	delete iWsEnv;
}

void CAppUi::ConstructL()
{
	BaseConstructL();
	iWsEnv = CSymTtkWsEnv::NewL(ApplicationRect());
}

void CAppUi::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EEikCmdExit: 
		Exit();
		break;
	}
}
