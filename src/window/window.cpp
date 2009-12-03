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

CWindowGc& CWindow::SystemGc()
{
	return *iClient.iGc;
}

CFont* CWindow::Font()
{
	return iFont;
}

CWindow::CWindow(CWsClient& aClient) : iClient(aClient)
{
}

void CWindow::ConstructL(const TRect& aRect, const TRgb& aColor,
			 CWindow* aParent)
{
	_LIT(KFontName, "Swiss");
	RWindowTreeNode* parent = aParent ? &(aParent->Window()) : &(iClient.iGroup);
	iWindow = RWindow(iClient.iWs);
	User::LeaveIfError(iWindow.Construct(*parent, (TUint32)this));
	iWindow.SetExtent(aRect.iTl, aRect.Size());
	iWindow.SetBackgroundColor (aColor);
	TFontSpec fontSpec(KFontName, 200);
	User::LeaveIfError(iClient.iScreen->GetNearestFontInTwips(iFont,fontSpec));
	iWindow.Activate();
}

