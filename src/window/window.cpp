#include <window/window.h>
#include <window/wsclient.h>

CWindow::~CWindow()
{
	iWindow.Close();
	iClient.iScreen->ReleaseFont(iFont);
}

RWindow& CWindow::Window()
{
	return iWindow;
}

CWindowGc* CWindow::SystemGc()
{
	return iClient.iGc;
}

CWsScreenDevice* CWindow::Screen()
{
	return iClient.iScreen;
}

CFont* CWindow::Font()
{
	return iFont;
}

CWindow::CWindow(CWsClient& aClient) : iClient(aClient)
{
}

void CWindow::ConstructL(const TRect& aRect, const TRgb& aColor, CWindow* aParent)
{
	_LIT(KFontName, "Swiss");
	// If a parent window was specified, use it; if not, use the window group
	// (aParent defaults to 0).
	RWindowTreeNode* parent = aParent ? (RWindowTreeNode*) &(aParent->Window()) : &(iClient.iGroup);
	// Allocate and construct the window
	iWindow=RWindow(iClient.iWs);
	User::LeaveIfError(iWindow.Construct(*parent,(TUint32)this));
	// Set up the new window's extent
	iWindow.SetExtent(aRect.iTl, aRect.Size());
	// Set its background color
	iWindow.SetBackgroundColor (aColor);
	// Set up font for displaying text
	TFontSpec fontSpec(KFontName, 200);
	User::LeaveIfError(iClient.iScreen->GetNearestFontInTwips(iFont,fontSpec));
	// Activate the window
	iWindow.Activate();
}

