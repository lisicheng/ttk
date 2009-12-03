#include "window/wsclient.h"
#include "window/wsredrawer.h"

CWsClient::CWsClient()
	: CActive(CActive::EPriorityStandard)
{
}

void CWsClient::ConstructL()
{
	// add ourselves to active scheduler 
	CActiveScheduler::Add(this);
	// get a session going
	User::LeaveIfError(iWs.Connect());
	// construct our one and only window group
	iGroup=RWindowGroup(iWs);
	User::LeaveIfError(iGroup.Construct(2,ETrue)); // '2' is a meaningless handle
	// construct screen device and graphics context
	iScreen=new (ELeave) CWsScreenDevice(iWs); // make device for this session
	User::LeaveIfError(iScreen->Construct()); // and complete its construction
	User::LeaveIfError(iScreen->CreateContext(iGc)); // create graphics context
	// construct redrawer
	iRedrawer=new (ELeave) CWsRedrawer;
	iRedrawer->ConstructL(this);
	// construct main window
	ConstructMainWindowL();
	// request first event and start scheduler
	IssueRequest();
}

CWsClient::~CWsClient()
{
	// neutralize us as an active object
	Deque(); // cancels and removes from scheduler
	// get rid of everything we allocated
	delete iGc;
	delete iScreen;
	delete iRedrawer;
	// destroy window group
	iGroup.Close(); // what's the difference between this and destroy?
	// finish with window server
	iWs.Close();
}

void CWsClient::IssueRequest()
{
	iWs.EventReady(&iStatus); // request an event
	SetActive(); // so we're now active
}

void CWsClient::DoCancel()
{
	iWs.EventReadyCancel(); // cancel event request
}

void CWsClient::ConstructMainWindowL()
{
}

