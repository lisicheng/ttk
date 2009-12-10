#include "symttk/wsenv.h"

#include "symttk/redrawer.h"
#include "symttk/window.h"
#include "ui/mainwidget.h"

CSymTtkWsEnv::~CSymTtkWsEnv()
{
	delete iRootWidget;
	delete iRedrawer;
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

CWindowGc& CSymTtkWsEnv::Gc() const
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
	TInt dummy = 2; // meaningless
	User::LeaveIfError(iGroup.Construct(dummy, ETrue));
	iScreen = new(ELeave) CWsScreenDevice(iWs);
	User::LeaveIfError(iScreen->Construct());
	User::LeaveIfError(iScreen->CreateContext(iGc));
	iRedrawer = CSymTtkRedrawer::NewL(*this);
	TtkRect rect(aRect.iTl.iX, aRect.iTl.iY,
		     aRect.iBr.iX, aRect.iBr.iY);
	iRootWidget = MainWidget::NewL(*this, rect);
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
	switch (event.Type()) {
	case EEventKey:
		iRootWidget->handle_key_event(*event.Key());
		break;
	case EEventPointer:
		reinterpret_cast<CSymTtkWindow*>(event.Handle())->
			Widget().handle_pointer_event(*event.Pointer());
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
