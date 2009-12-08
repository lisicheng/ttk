#include <window/window.h>
#include <window/wsclient.h>

CWindow::~CWindow()
{
	iWindow.Close();
}

RWindow& CWindow::Window()
{
	return iWindow;
}

CWindow::CWindow(CWsClient& aClient) : iClient(aClient)
{
}

void CWindow::ConstructL(const TRect& aRect, const TRgb& aColor)
{
	const RWindowTreeNode* parent;
	parent = static_cast<const RWindowTreeNode*>(&(iClient.Group()));
	iWindow = RWindow(iClient.Ws());
	User::LeaveIfError(iWindow.Construct(*parent,
					     reinterpret_cast<TUint32>(this)));
	iWindow.SetExtent(aRect.iTl, aRect.Size());
	iWindow.SetBackgroundColor(aColor);

	iWindow.Activate();
}
