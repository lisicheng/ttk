#include "window/wsclient.h"

#include "ui/mainwidget.h"
#include "window/window.h"
#include "window/wsredrawer.h"

CWsClient::~CWsClient()
{
	delete iRootWidget;
	delete iRedrawer;
	delete iGc;
	delete iScreen;
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

RWsSession& CWsClient::Ws()
{
	return iWs;
}

const RWindowGroup& CWsClient::Group() const
{
	return iGroup;
}

CWsScreenDevice& CWsClient::Screen() const
{
	return *iScreen;
}

CWindowGc& CWsClient::Gc() const
{
	return *iGc;
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
	iScreen = new(ELeave) CWsScreenDevice(iWs);
	User::LeaveIfError(iScreen->Construct());
	User::LeaveIfError(iScreen->CreateContext(iGc));
	iRedrawer = CWsRedrawer::NewL(*this);
	iRootWidget = CMainWidget::NewL(*this, aRect);
	IssueRequest();
}

void CWsClient::DoCancel()
{
	iWs.EventReadyCancel();
}

void CWsClient::RunL()
{
	TWsEvent event;
	Ws().GetEvent(event);
	switch (event.Type()) {
	case EEventKey:
		iRootWidget->HandleKeyEventL(*event.Key());
		break;
	case EEventPointer:
		reinterpret_cast<CWindow*>(event.Handle())->
			Widget().HandlePointerEventL(*event.Pointer());
		break;
	default:
		break;
	}
	IssueRequest();
}

void CWsClient::IssueRequest()
{
	iWs.EventReady(&iStatus);
	SetActive();
}
