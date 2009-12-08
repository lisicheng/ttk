#include "window/widget.h"
#include "window/wsclient.h"
#include "window/window.h"
#include "window/wsredrawer.h"

CWidget::~CWidget()
{
	if (iOwnWindow)
		delete iWindow;
}

CWindow& CWidget::Window()
{
	return *iWindow;
}

TRect& CWidget::Rect()
{
	return iRect;
}

CWsClient& CWidget::WsEnv()
{
	return iWsEnv;
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

CWidget::CWidget(CWsClient& aWsEnv) : iWsEnv(aWsEnv)
{
}

void CWidget::ConstructL(const CWindow* aWindow, const TRect& aRect)
{
	if (aWindow) {
		iWindow = aWindow;
		iOwnWindow = EFalse;
	} else {
		iWindow = CWindow::NewL(iWsEnv, aRect, *this, KRgbWhite);
		iOwnWindow = ETrue;
	}
	iRect = aRect;
	/*
	_LIT(KFontName, "Swiss");
	const TInt KFontHeight = 200;
	TFontSpec fontSpec(KFontName, KFontHeight);
	TFont font;
	User::LeaveIfError(iWsEnv.Screen().GetNearestFontInTwips(font,
								 fontSpec));
	iWsEnv.Screen().ReleaseFont(font);
	*/
}
