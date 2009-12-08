#include "window/wsclient.h"
#include "window/wsredrawer.h"

CWsClient::~CWsClient()
{
	delete iGc;
	delete iRedrawer;
	delete iScreen;
	iGroup.Close();
	iWs.Close();
}

void CWsClient::DoCancel()
{
	iWs.EventReadyCancel(); // cancel event request
}

RWsSession& CWsClient::Ws()
{
	return iWs;
}

const RWindowGroup& CWsClient::Group() const
{
	return iGroup;
}

CWsScreenDevice& CWsClient::Screen()
{
	return *iScreen;
}

CWindowGc& CWsClient::Gc()
{
	return *iGc;
}

void CWsClient::IssueRequest()
{
	iWs.EventReady(&iStatus);
	SetActive();
}

void CWsClient::ConstructMainWindowL()
{
}

CWsClient::CWsClient() : CActive(CActive::EPriorityStandard)
{
}

void CWsClient::ConstructL()
{
	CActiveScheduler::Add(this);
	User::LeaveIfError(iWs.Connect());
	iGroup = RWindowGroup(iWs);
	TInt dummy = 2; // meaningless
	User::LeaveIfError(iGroup.Construct(dummy, ETrue));
	iScreen = new(ELeave) CWsScreenDevice(iWs); // make device for this session
	User::LeaveIfError(iScreen->Construct());
	User::LeaveIfError(iScreen->CreateContext(iGc)); // create graphics context
	iRedrawer = CWsRedrawer::NewL(*this);
	ConstructMainWindowL();
	IssueRequest();
}

void CWsClient::RunL()
{
	TWsEvent event;
	Ws().GetEvent(event);
	if (event.Type() == EEventKey && iRootWidget)
		iRootWidget->HandleKeyEventL(*event.Key());
	}
	IssueRequest();
}

void CWsClient::SetRootWidget(CWidget* aRootWidget)
{
	iRootWidget = aRootWidget;
}
