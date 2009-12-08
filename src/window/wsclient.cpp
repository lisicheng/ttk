#include "window/wsclient.h"
#include "window/wsredrawer.h"
#include "ui/mainwidget.h"

CWsClient::~CWsClient()
{
	delete iGc;
	delete iRedrawer;
	delete iScreen;
	delete iRootWidget;
	iGroup.Close();
	iWs.Close();
}

CWsClient* CWsClient::NewL(const TRect& aRect)
{
	CWsClient* self = CWsClient::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
}

CWsClient* CWsClient::NewLC(const TRect& aRect)
{
	CWsClient* self = new(ELeave) CWsClient();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
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

CWindowGc& CWsClient::Gc() const
{
	return *iGc;
}

void CWsClient::IssueRequest()
{
	iWs.EventReady(&iStatus);
	SetActive();
}

CWsClient::CWsClient() : CActive(CActive::EPriorityStandard)
{
}

void CWsClient::ConstructL(const TRect& aRect)
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
	iRootWidget = CMainWidget::NewL(*this, NULL, aRect);
	IssueRequest();
}

void CWsClient::RunL()
{
	TWsEvent event;
	Ws().GetEvent(event);
	if (event.Type() == EEventKey)
		iRootWidget->HandleKeyEventL(*event.Key());
	IssueRequest();
}
