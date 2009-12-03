#include "window/wsredrawer.h"
#include "window/window.h"
#include "window/wsclient.h"

CWsRedrawer::~CWsRedrawer()
{
	Cancel();
}

CWsRedrawer* CWsRedrawer::NewL(CWsClient& aClient)
{
	CWsRedrawer* self = CWsRedrawer::NewLC(aClient);
	CleanupStack::Pop(self);
	return self;
}

CWsRedrawer* CWsRedrawer::NewLC(CWsClient& aClient)
{
	CWsRedrawer* self = new(ELeave) CWsRedrawer(aClient);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

void CWsRedrawer::DoCancel()
{
	iClient.iWs.RedrawReadyCancel();
}

void CWsRedrawer::RunL()
{	
	TWsRedrawEvent event;
	iClient.iWs.GetRedraw(event);
	CWindow* window = reinterpret_cast<CWindow*>(event.Handle());
	if (window) {
		iClient.iGc->Activate(window->Window());
		window->Window().BeginRedraw();
		window->Draw(event.Rect());
		window->Window().EndRedraw();
		iClient.iGc->Deactivate();
	}
	IssueRequest();
}

void CWsRedrawer::IssueRequest()
{
	iClient.iWs.RedrawReady(&iStatus);
	SetActive();
}

CWsRedrawer::CWsRedrawer(CWsClient& aClient)
	: CActive(CActive::EPriorityLow), iClient(aClient)
{
}

void CWsRedrawer::ConstructL()
{
	CActiveScheduler::Add(this);
	IssueRequest();
}
