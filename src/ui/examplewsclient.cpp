#include "ui/examplewsclient.h"
#include "ui/mainwindow.h"
#include "ui/numberedwindow.h"

CExampleWsClient* CExampleWsClient::NewL(const TRect& aRect)
{
	// make new client
	CExampleWsClient* client=new (ELeave) CExampleWsClient(aRect); 
	CleanupStack::PushL(client); // push, just in case
	client->ConstructL(); // construct and run
	CleanupStack::Pop();
	return client;
}

/****************************************************************************\
|	Function:	Constructor/Destructor for CExampleWsClient
|				Destructor deletes everything that was allocated by
|				ConstructMainWindowL()
\****************************************************************************/
CExampleWsClient::CExampleWsClient(const TRect& aRect)
		:iRect(aRect)
{
}

CExampleWsClient::~CExampleWsClient ()
{
	delete iMainWindow;
	delete iWindow1;
}

/****************************************************************************\
|	Function:	CExampleWsClient::ConstructMainWindowL()
|				Called by base class's ConstructL
|	Purpose:	Allocates and creates all the windows owned by this client
|				(See list of windows in CExampleWsCLient declaration).
\****************************************************************************/
void CExampleWsClient::ConstructMainWindowL()
{
	iMainWindow = CMainWindow::NewL(this, iRect, TRgb(255,255,255));
	TRect rec(iRect);
	rec.Resize(-50,-50);
	iWindow1 = CNumberedWindow::NewL(this, 1, rec, TRgb(200, 200, 200),
					 iMainWindow);
}

/****************************************************************************\
|	Function:	CExampleWsClient::RunL()
|				Called by active scheduler when an even occurs
|	Purpose:	Processes events according to their type
|				For key events: calls HandleKeyEventL() (global to client)
|				For pointer event: calls HandlePointerEvent() for window
|                                  event occurred in.
\****************************************************************************/
void CExampleWsClient::RunL()
{
	// get the event
	iWs.GetEvent(iWsEvent);
	TInt eventType=iWsEvent.Type();
	// take action on it
	switch (eventType) {
	// events global within window group
	case EEventNull:
		break;
	case EEventKey: {
			TKeyEvent& keyEvent=*iWsEvent.Key(); // get key event
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
			CWindow* window=(CWindow*)(iWsEvent.Handle()); // get window
			TPointerEvent& pointerEvent=*iWsEvent.Pointer();
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

/****************************************************************************\
|	Function:	CExampleWsClient::HandleKeyEventL()
|	Purpose:	Processes key events for CExampleWsClient
\****************************************************************************/
void CExampleWsClient::HandleKeyEventL (TKeyEvent& /*aKeyEvent*/)
{
}

