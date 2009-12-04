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
	const RWindowTreeNode* parent;
	if (aParent)
		parent = static_cast<const RWindowTreeNode*>
				    (&(aParent->Window()));
	else
		parent = static_cast<const RWindowTreeNode*>
				    (&(iClient.Group()));
	iWindow = RWindow(iClient.Ws());
	User::LeaveIfError(iWindow.Construct(*parent,
					     reinterpret_cast<TUint32>(this)));
	iWindow.SetExtent(aRect.iTl, aRect.Size());
	iWindow.SetBackgroundColor(aColor);

	_LIT(KFontName, "Swiss");
	const TInt KFontHeight = 200;
	TFontSpec fontSpec(KFontName, KFontHeight);
	User::LeaveIfError(iClient.Screen().GetNearestFontInTwips(iFont,fontSpec));

	iWindow.Activate();
}
