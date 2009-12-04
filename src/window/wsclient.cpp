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
	iWs.EventReady(&iStatus); // request an event
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
	// '2' is a meaningless handle
	User::LeaveIfError(iGroup.Construct(2, ETrue));
	iScreen = new(ELeave) CWsScreenDevice(iWs); // make device for this session
	User::LeaveIfError(iScreen->Construct());
	User::LeaveIfError(iScreen->CreateContext(iGc)); // create graphics context
	iRedrawer = CWsRedrawer::NewL(*this);
	ConstructMainWindowL();
	IssueRequest();
}
