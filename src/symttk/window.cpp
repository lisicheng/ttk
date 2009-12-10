#include "symttk/window.h"

#include "symttk/wsenv.h"
#include "ttk/widget.h"

CWindow::~CWindow()
{
	iWindow.Close();
}

CWindow* CWindow::NewL(CWidget& aWidget, const TRgb& aColor)
{
	CWindow* self = CWindow::NewLC(aWidget, aColor);
	CleanupStack::Pop(self);
	return self;
}

CWindow* CWindow::NewLC(CWidget& aWidget, const TRgb& aColor)
{
	CWindow* self = new(ELeave) CWindow(aWidget);
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

CWindow::CWindow(CWidget& aWidget) : iWidget(aWidget)
{
}

void CWindow::ConstructL(const TRgb& aColor)
{
	iWindow = RWindow(iWidget.WsEnv().Ws());
	User::LeaveIfError(iWindow.Construct(iWidget.WsEnv().Group(),
					     reinterpret_cast<TUint32>(this)));
	iWindow.SetExtent(iWidget.Rect().iTl, iWidget.Rect().Size());
	iWindow.SetBackgroundColor(aColor);

	iWindow.Activate();
}
