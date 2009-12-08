#include "window/wsredrawer.h"
#include "window/widget.h"
#include "window/window.h"
#include "window/wsclient.h"

CWsRedrawer::~CWsRedrawer()
{
	Cancel();
}

CWsRedrawer* CWsRedrawer::NewL(CWsClient& aWsEnv)
{
	CWsRedrawer* self = CWsRedrawer::NewLC(aWsEnv);
	CleanupStack::Pop(self);
	return self;
}

CWsRedrawer* CWsRedrawer::NewLC(CWsClient& aWsEnv)
{
	CWsRedrawer* self = new(ELeave) CWsRedrawer(aWsEnv);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

void CWsRedrawer::DoCancel()
{
	iWsEnv.Ws().RedrawReadyCancel();
}

void CWsRedrawer::RunL()
{	
	TWsRedrawEvent event;
	iWsEnv.Ws().GetRedraw(event);
	CWindow* window = reinterpret_cast<CWindow*>(event.Handle());
	if (window) {
		iWsEnv.Gc().Activate(window->Window());
		window->Window().BeginRedraw();
		window->RootWidget().Draw(event.Rect());
		window->Window().EndRedraw();
		iWsEnv.Gc().Deactivate();
	}
	IssueRequest();
}

void CWsRedrawer::IssueRequest()
{
	iWsEnv.Ws().RedrawReady(&iStatus);
	SetActive();
}

CWsRedrawer::CWsRedrawer(CWsClient& aWsEnv)
	: CActive(CActive::EPriorityLow), iWsEnv(aWsEnv)
{
}

void CWsRedrawer::ConstructL()
{
	CActiveScheduler::Add(this);
	IssueRequest();
}
