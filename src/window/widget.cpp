#include "window/widget.h"
#include "window/wsclient.h"
#include "window/wsredrawer.h"

CWidget::~CWidget()
{
	if (iOwnWindow)
		delete iWindow;
}

CWidget::CWidget(CWsClient& aWsEnv) : iWsEnv(aWsEnv)
{
}

CWindow* CWidget::Window()
{
	return iWindow;
}

CWsClient& CWidget::WsEnv()
{
	return iWsEnv;
}

void CWidget::ConstructL(const CWideget* aParent, const TRect& aRect)
{
	if (aParent) {
		iWindow = aParent->Window();
		iOwnWindow = EFalse;
	} else {
		iWindow = CWindow::NewL(*this, aRect)
		iOwnWindow = ETrue;
	}
	iRect = aRect;
	_LIT(KFontName, "Swiss");
	const TInt KFontHeight = 200;
	TFontSpec fontSpec(KFontName, KFontHeight);
	TFont font;
	User::LeaveIfError(iWsEnv.Screen().GetNearestFontInTwips(font,
								 fontSpec));
	iWsEnv.Screen().ReleaseFont(font);
}

void CWidget::HandleKeyEventL(TKeyEvent& aKeyEvent)
{
	return;
}

void CWidget::Draw(const TRect& aRect)
{
	CWindowGc& gc = WsEnv().Gc();
	gc.Clear(aRect);
}
