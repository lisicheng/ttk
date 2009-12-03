#include "ui/examplewsclient.h"
#include "ui/mainwindow.h"
#include "ui/numberedwindow.h"

CExampleWsClient::~CExampleWsClient ()
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

CExampleWsClient::CExampleWsClient(const TRect& aRect) :iRect(aRect)
{
}

/**
 * Called by base class's ConstructL.
 * Allocates and creates all the windows owned by this client.
 * (See list of windows in CExampleWsCLient declaration).
 */
void CExampleWsClient::ConstructMainWindowL()
{
	iMainWindow = CMainWindow::NewL(*this, iRect, TRgb(255, 255, 255));
	TRect rec(iRect);
	rec.Resize(-50, -50);
	iWindow1 = CNumberedWindow::NewL(*this, 1, rec, TRgb(200, 200, 200),
					 iMainWindow);
}

/**
 * Processes events according to their type
 * For key events: calls HandleKeyEventL() (global to client)
 * For pointer event: calls HandlePointerEvent() for window event occurred in.
 */
void CExampleWsClient::RunL()
{
	TWsEvent event;
	iWs.GetEvent(event);
	TInt eventType = event.Type();
	// take action on it
	switch (eventType) {
	// events global within window group
	case EEventNull:
		break;
	case EEventKey: {
			TKeyEvent& keyEvent=*event.Key(); // get key event
			HandleKeyEventL (keyEvent);
			break;
		}
	case EEventModifiersChanged:
		break;
	case EEventKeyUp:
	case EEventKeyDown:
	case EEventFocusLost:
	case EEventFocusGained:
	case EEventSwitchOn:
	case EEventPassword:
	case EEventWindowGroupsChanged:
	case EEventErrorMessage:
		break;
	// events local to specific windows
	case EEventPointer: {
			CWindow* window=(CWindow*)(event.Handle()); // get window
			TPointerEvent& pointerEvent=*event.Pointer();
			window->HandlePointerEvent (pointerEvent);
			break;
		}
	case EEventPointerExit:
	case EEventPointerEnter:
	case EEventPointerBufferReady:
	case EEventDragDrop:
		break;
	default:
		break;
	}
	IssueRequest(); // maintain outstanding request
}

void CExampleWsClient::HandleKeyEventL(TKeyEvent& /*aKeyEvent*/)
{
}

