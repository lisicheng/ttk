#include "symttk/wsenv.h"

#include "symttk/redrawer.h"
#include "symttk/window.h"
#include "symttk/gc.h"
#include "symttk/imagedecoder.h"
#include "example/mainwidget.h"
#include "example/mainwidget2.h"
#include "ttk/common/pointerevent.h"

CSymTtkWsEnv::~CSymTtkWsEnv()
{
	delete iRootWidget;
	delete iRedrawer;
	delete iImageDecoder;
	delete iGc;
	delete iScreen;
	iGroup.Close();
	iWs.Close();
}

CSymTtkWsEnv* CSymTtkWsEnv::NewL(const TRect& aRect)
{
	CSymTtkWsEnv* self = CSymTtkWsEnv::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
}

CSymTtkWsEnv* CSymTtkWsEnv::NewLC(const TRect& aRect)
{
	CSymTtkWsEnv* self = new(ELeave) CSymTtkWsEnv();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
}

TtkWindowInterface* CSymTtkWsEnv::new_window(TtkWidget& widget,
					     TtkColor color) const
{
#ifdef EKA2
	TRgb rgb;
	rgb.SetInternal(color);
#else
	TRgb rgb(color);
#endif
	return CSymTtkWindow::NewL(widget, rgb);
}

TtkGcInterface& CSymTtkWsEnv::gc() const
{
	return *iGc;
}

TtkImageDecoderInterface& CSymTtkWsEnv::image_decoder() const
{
	return *iImageDecoder;
}

RWsSession& CSymTtkWsEnv::Ws()
{
	return iWs;
}

const RWindowGroup& CSymTtkWsEnv::Group() const
{
	return iGroup;
}

CWsScreenDevice& CSymTtkWsEnv::Screen() const
{
	return *iScreen;
}

CSymTtkGc& CSymTtkWsEnv::Gc() const
{
	return *iGc;
}

CSymTtkWsEnv::CSymTtkWsEnv() : CActive(CActive::EPriorityStandard)
{
}

void CSymTtkWsEnv::ConstructL(const TRect& aRect)
{
	CActiveScheduler::Add(this);
	User::LeaveIfError(iWs.Connect());
	iGroup = RWindowGroup(iWs);
	TInt dummy = 2; /* meaningless */
	User::LeaveIfError(iGroup.Construct(dummy, ETrue));
	iScreen = new(ELeave) CWsScreenDevice(iWs);
	User::LeaveIfError(iScreen->Construct());
	iGc = CSymTtkGc::NewL(*iScreen);
	iImageDecoder = CSymTtkImageDecoder::NewL();
	iRedrawer = CSymTtkRedrawer::NewL(*this);
	TtkRect rect(aRect.iTl.iX, aRect.iTl.iY,
		     aRect.iBr.iX, aRect.iBr.iY);
	//iRootWidget = new MainWidget(*this, rect);
	iRootWidget = new MainWidget2(*this, rect);
	IssueRequest();
}

void CSymTtkWsEnv::DoCancel()
{
	iWs.EventReadyCancel();
}

void CSymTtkWsEnv::RunL()
{
	TWsEvent event;
	Ws().GetEvent(event);
	TtkKeyEvent key_event;
	TtkPointerEvent pointer_event;
	switch (event.Type()) {
	case EEventKey:
		switch (event.Key()->iCode) {
		case EKeyUpArrow:
			key_event = kTtkKeyUp;
			break;
		case EKeyDownArrow:
			key_event = kTtkKeyDown;
			break;
		default:
			key_event = kTtkKeyUnknown;
			break;
		}
		iRootWidget->handle_key_event(key_event);
		break;
	case EEventPointer:
		/* TODO: pointer_event */
		reinterpret_cast<CSymTtkWindow*>(event.Handle())->
			Widget().handle_pointer_event(pointer_event);
		break;
	default:
		break;
	}
	IssueRequest();
}

void CSymTtkWsEnv::IssueRequest()
{
	iWs.EventReady(&iStatus);
	SetActive();
}
