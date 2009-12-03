#include "window/wsredrawer.h"
#include "window/window.h"
#include "window/wsclient.h"

CWsRedrawer::~CWsRedrawer()
{
	Cancel();
}

CWsRedrawer* CWsRedrawer::NewL(CWsClient* aClient)
{
	CWsRedrawer* self = CWsRedrawer::NewLC(aClient);
	CleanupStack::Pop(self);
	return self;
}

CWsRedrawer* CWsRedrawer::NewLC(CWsClient* aClient)
{
	CWsRedrawer* self = new(ELeave) CWsRedrawer();
	CleanupStack::PushL(self);
	self->ConstructL(aClient);
	return self;
}

void CWsRedrawer::IssueRequest()
{
	iClient->iWs.RedrawReady(&iStatus);
	SetActive();
}

void CWsRedrawer::DoCancel()
{
	iClient->iWs.RedrawReadyCancel();
}

void CWsRedrawer::RunL()
{	
	// find out what needs to be done in response to the event
	TWsRedrawEvent redrawEvent;
	iClient->iWs.GetRedraw(redrawEvent); // get event
	CWindow* window = (CWindow*)(redrawEvent.Handle()); // get window
	if (window) {
		TRect rect=redrawEvent.Rect(); // and rectangle that needs redrawing
		// now do drawing
		iClient->iGc->Activate(window->Window());
		window->Window().BeginRedraw();
		window->Draw(rect);
		window->Window().EndRedraw();
		iClient->iGc->Deactivate();
	}
	// maintain outstanding request
	IssueRequest();
}

CWsRedrawer::CWsRedrawer() : CActive(CActive::EPriorityLow)
{
}

void CWsRedrawer::ConstructL(CWsClient* aClient)
{
	iClient=aClient; // remember WsClient that owns us
	CActiveScheduler::Add(this); // add ourselves to the scheduler
	IssueRequest(); // issue request to draw
}

