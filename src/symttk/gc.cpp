#include "symttk/gc.h"

#include "ttk/common/rect.h"

void CSymTtkGc::clear(const TtkRect& rect)
{
	TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
		       rect.br_.x_, rect.br_.y_);
	CWindowGc::Clear(sym_rect);
}

CSymTtkGc::CSymTtkGc(CWsScreenDevice* aDevice) : CWindowGc(aDevice)
{
}
