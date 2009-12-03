#include "window/wsclient.h"
#include "window/wsredrawer.h"

CWsClient::~CWsClient()
{
	// neutralize us as an active object
	Deque(); // cancels and removes from scheduler
	delete iGc;
	delete iScreen;
	delete iRedrawer;
	iGroup.Close(); // what's the difference between this and destroy?
	iWs.Close();
}

void CWsClient::DoCancel()
{
	iWs.EventReadyCancel(); // cancel event request
}

void CWsClient::IssueRequest()
{
	iWs.EventReady(&iStatus); // request an event
	SetActive(); // so we're now active
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
	// '2' is a meaningless handle
	User::LeaveIfError(iGroup.Construct(2, ETrue));
	iScreen = new(ELeave) CWsScreenDevice(iWs); // make device for this session
	User::LeaveIfError(iScreen->Construct());
	User::LeaveIfError(iScreen->CreateContext(iGc)); // create graphics context
	iRedrawer = CWsRedrawer::NewL(this);
	ConstructMainWindowL();
	IssueRequest();
}

