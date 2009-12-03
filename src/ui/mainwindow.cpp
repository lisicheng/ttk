#include "ui/mainwindow.h"

CMainWindow::CMainWindow (CWsClient* aClient)
		: CWindow (aClient)
{
}

CMainWindow::~CMainWindow ()
{
	iWindow.Close();
}

/****************************************************************************\
|	Function:	CMainWindow::Draw
|	Purpose:	Redraws the contents of CMainWindow within a given
|				rectangle.
|	Input:		aRect	Rectangle that needs redrawing
|	Output:		None
\****************************************************************************/
void CMainWindow::Draw(const TRect& aRect)
{
	CWindowGc* gc=SystemGc(); // get a gc
	gc->SetClippingRect(aRect); // clip outside this rect
	gc->Clear(aRect); // clear
}

/****************************************************************************\
|	Function:	CMainWindow::HandlePointerEvent
|	Purpose:	Handles pointer events for CMainWindow.
|	Input:		aPointerEvent	The pointer event!
|	Output:		None
\****************************************************************************/
void CMainWindow::HandlePointerEvent (TPointerEvent& aPointerEvent)
{	
	switch (aPointerEvent.iType) {
	case TPointerEvent::EButton1Down:
	case TPointerEvent::EButton1Up:
		break;
	default:
		break;
	}
}

