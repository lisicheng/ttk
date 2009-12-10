#include "symttk/gc.h"

#include "ttk/common/rect.h"

CSymTtkGc::~CSymTtkGc()
{
	delete iGc;
}

CSymTtkGc* CSymTtkGc::NewL(CWsScreenDevice& aScreen)
{
	CSymTtkGc* self = CSymTtkGc::NewLC(aScreen);
	CleanupStack::Pop(self);
	return self;
}

CSymTtkGc* CSymTtkGc::NewLC(CWsScreenDevice& aScreen)
{
	CSymTtkGc* self = new(ELeave) CSymTtkGc();
	CleanupStack::PushL(self);
	self->ConstructL(aScreen);
	return self;
}

void CSymTtkGc::clear(const TtkRect& rect)
{
	const TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
			     rect.br_.x_, rect.br_.y_);
	iGc->Clear(sym_rect);
}

void CSymTtkGc::draw_line(const TtkPoint& p1, const TtkPoint& p2)
{
	const TPoint sym_p1(p1.x_, p1.y_);
	const TPoint sym_p2(p2.x_, p2.y_);
	iGc->DrawLine(sym_p1, sym_p2);
}

void CSymTtkGc::set_clipping_rect(const TtkRect& rect)
{
	const TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
			     rect.br_.x_, rect.br_.y_);
	iGc->SetClippingRect(sym_rect);
}

void CSymTtkGc::set_pen_color(TtkColor color)
{
	const TRgb sym_color(color & kTtkColorRawRed,
			     color & kTtkColorRawGreen,
			     color & kTtkColorRawBlue,
			     color & kTtkColorRawAlpha);
	iGc->SetPenColor(sym_color);
}

CWindowGc& CSymTtkGc::Gc() const
{
	return *iGc;
}

void CSymTtkGc::ConstructL(CWsScreenDevice& aScreen)
{
	User::LeaveIfError(aScreen.CreateContext(iGc));
}
