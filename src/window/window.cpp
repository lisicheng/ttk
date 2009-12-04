#include <window/window.h>
#include <window/wsclient.h>

CWindow::~CWindow()
{
	iWindow.Close();
	iClient.Screen().ReleaseFont(iFont);
}

RWindow& CWindow::Window()
{
	return iWindow;
}

CWindowGc& CWindow::SystemGc()
{
	return iClient.Gc();
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
	const RWindowTreeNode* parent;
	if (aParent)
		parent = static_cast<const RWindowTreeNode*>(&(aParent->Window()));
	else
		parent = static_cast<const RWindowTreeNode*>(&(iClient.Group()));
	iWindow = RWindow(iClient.Ws());
	User::LeaveIfError(iWindow.Construct(*parent, (TUint32)this));
	iWindow.SetExtent(aRect.iTl, aRect.Size());
	iWindow.SetBackgroundColor (aColor);
	TFontSpec fontSpec(KFontName, 200);
	User::LeaveIfError(iClient.Screen().GetNearestFontInTwips(iFont,fontSpec));
	iWindow.Activate();
}

