#include "ui/examplewsclient.h"
#include "ui/mainwindow.h"
#include "ui/numberedwindow.h"

CExampleWsClient::~CExampleWsClient()
{
	delete iMainWindow;
	delete iWindow1;
}

CExampleWsClient* CExampleWsClient::NewL(const TRect& aRect)
{
	CExampleWsClient* self = CExampleWsClient::NewLC(aRect); 
	CleanupStack::Pop(self);
	return self;
}

CExampleWsClient* CExampleWsClient::NewLC(const TRect& aRect)
{
	CExampleWsClient* self = new(ELeave) CExampleWsClient(aRect); 
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CExampleWsClient::CExampleWsClient(const TRect& aRect) : iRect(aRect)
{
}

/**
 * Processes events according to their type
 * For key events: calls HandleKeyEventL() (global to client)
 * For pointer event: calls HandlePointerEvent() for window event occurred in.
 */
void CExampleWsClient::RunL()
{
	TWsEvent event;
	Ws().GetEvent(event);
	switch (event.Type()) {
	case EEventKey:
		HandleKeyEventL(*event.Key());
		break;
	default:
		break;
	}
	IssueRequest();
}

/**
 * Called by base class's ConstructL.
 * Allocates and creates all the windows owned by this client.
 */
void CExampleWsClient::ConstructMainWindowL()
{
	iMainWindow = CMainWindow::NewL(*this, iRect, KRgbWhite);
	TRect rect(iRect);
	rect.Resize(-50, -50);
	iWindow1 = CNumberedWindow::NewL(*this, 1, rect, KRgbGray, iMainWindow);
}

