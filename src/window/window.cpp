#include "window/window.h"
#include "window/wsclient.h"
#include "common.h"

CWindow::~CWindow()
{
	iWindow.Close();
}

CWindow* CWindow::NewL(CWsClient& aWsEnv, const TRect aRect,
		       CWidget& aRootWidget, const TRgb& aColor)
{
	CWindow* self = CWindow::NewLC(aWsEnv, aRect, aRootWidget, aColor);
	CleanupStack::Pop(self);
	return self;
}

CWindow* CWindow::NewLC(CWsClient& aWsEnv, const TRect aRect,
			CWidget& aRootWidget, const TRgb& aColor)
{
	CWindow* self = new(ELeave) CWindow(aWsEnv, aRootWidget);
	self->ConstructL(aRect, aColor);
	CleanupStack::PushL(self);
	return self;
}

RWindow& CWindow::Window()
{
	return iWindow;
}

CWidget& CWindow::RootWidget()
{
	return iRootWidget;
}

CWindow::CWindow(CWsClient& aWsEnv, CWidget& aRootWidget)
		: iWsEnv(aWsEnv), iRootWidget(aRootWidget)
{
}

void CWindow::ConstructL(const TRect& aRect, const TRgb& aColor)
{
	LOG("window:construct");
	const RWindowTreeNode* parent;
	parent = static_cast<const RWindowTreeNode*>(&(iWsEnv.Group()));
	iWindow = RWindow(iWsEnv.Ws());
	User::LeaveIfError(iWindow.Construct(*parent,
					     reinterpret_cast<TUint32>(this)));
	iWindow.SetExtent(aRect.iTl, aRect.Size());
	iWindow.SetBackgroundColor(aColor);

	iWindow.Activate();
}
