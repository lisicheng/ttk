#include "symttk/redrawer.h"

#include "symttk/window.h"
#include "symttk/wsenv.h"
#include "ttk/widget.h"

CSymTtkRedrawer::~CSymTtkRedrawer()
{
	Cancel();
}

CSymTtkRedrawer* CSymTtkRedrawer::NewL(CSymTtkWsEnv& aWsEnv)
{
	CSymTtkRedrawer* self = CSymTtkRedrawer::NewLC(aWsEnv);
	CleanupStack::Pop(self);
	return self;
}

CSymTtkRedrawer* CSymTtkRedrawer::NewLC(CSymTtkWsEnv& aWsEnv)
{
	CSymTtkRedrawer* self = new(ELeave) CSymTtkRedrawer(aWsEnv);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CSymTtkRedrawer::CSymTtkRedrawer(CSymTtkWsEnv& aWsEnv)
		: CActive(CActive::EPriorityLow), iWsEnv(aWsEnv)
{
}

void CSymTtkRedrawer::ConstructL()
{
	CActiveScheduler::Add(this);
	IssueRequest();
}

void CSymTtkRedrawer::DoCancel()
{
	iWsEnv.Ws().RedrawReadyCancel();
}

void CSymTtkRedrawer::RunL()
{	
	TWsRedrawEvent event;
	iWsEnv.Ws().GetRedraw(event);
	CSymTtkWindow* window = reinterpret_cast<CSymTtkWindow*>(event.Handle());
	if (window) {
		iWsEnv.Gc().Activate(window->Window());
		window->Window().BeginRedraw();
		window->Widget().Draw(event.Rect());
		window->Window().EndRedraw();
		iWsEnv.Gc().Deactivate();
	}
	IssueRequest();
}

void CSymTtkRedrawer::IssueRequest()
{
	iWsEnv.Ws().RedrawReady(&iStatus);
	SetActive();
}
