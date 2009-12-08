#include "window/window.h"
#include "window/wsclient.h"
#include "window/widget.h"
#include "common.h"

CWindow::~CWindow()
{
	iWindow.Close();
}

CWindow* CWindow::NewL(CWsClient& aWsEnv, CWidget& aWidget, const TRgb& aColor)
{
	CWindow* self = CWindow::NewLC(aWsEnv, aWidget, aColor);
	CleanupStack::Pop(self);
	return self;
}

CWindow* CWindow::NewLC(CWsClient& aWsEnv, CWidget& aWidget, const TRgb& aColor)
{
	CWindow* self = new(ELeave) CWindow(aWsEnv, aWidget);
	self->ConstructL(aColor);
	CleanupStack::PushL(self);
	return self;
}

CWidget& CWindow::Widget()
{
	return iWidget;
}

RWindow& CWindow::Window()
{
	return iWindow;
}

CWindow::CWindow(CWsClient& aWsEnv, CWidget& aWidget)
		: iWsEnv(aWsEnv), iWidget(aWidget)
{
}

void CWindow::ConstructL(const TRgb& aColor)
{
	iWindow = RWindow(iWsEnv.Ws());
	User::LeaveIfError(iWindow.Construct(iWsEnv.Group(),
					     reinterpret_cast<TUint32>(this)));
	iWindow.SetExtent(iWidget.Rect().iTl, iWidget.Rect().Size());
	iWindow.SetBackgroundColor(aColor);

	iWindow.Activate();
}
