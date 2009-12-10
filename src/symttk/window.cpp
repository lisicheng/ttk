#include "symttk/window.h"

#include "symttk/wsenv.h"
#include "ttk/widget.h"

CSymTtkWindow::~CSymTtkWindow()
{
	iWindow.Close();
}

CSymTtkWindow* CSymTtkWindow::NewL(TtkWidget& aWidget, const TRgb& aColor)
{
	CSymTtkWindow* self = CSymTtkWindow::NewLC(aWidget, aColor);
	CleanupStack::Pop(self);
	return self;
}

CSymTtkWindow* CSymTtkWindow::NewLC(TtkWidget& aWidget, const TRgb& aColor)
{
	CSymTtkWindow* self = new(ELeave) CSymTtkWindow(aWidget);
	self->ConstructL(aColor);
	CleanupStack::PushL(self);
	return self;
}

TtkWidget& CSymTtkWindow::Widget()
{
	return iWidget;
}

RWindow& CSymTtkWindow::Window()
{
	return iWindow;
}

CSymTtkWindow::CSymTtkWindow(TtkWidget& aWidget) : iWidget(aWidget)
{
}

void CSymTtkWindow::ConstructL(const TRgb& aColor)
{
	iWindow = RWindow(iWidget.WsEnv().Ws());
	User::LeaveIfError(iWindow.Construct(iWidget.WsEnv().Group(),
					     reinterpret_cast<TUint32>(this)));
	iWindow.SetExtent(iWidget.Rect().iTl, iWidget.Rect().Size());
	iWindow.SetBackgroundColor(aColor);

	iWindow.Activate();
}
