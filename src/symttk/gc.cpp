#include "symttk/gc.h"

#include <utf.h>
#include "ttk/common/rect.h"

CSymTtkGc::~CSymTtkGc()
{
	iScreen.ReleaseFont(iFont);
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
	CSymTtkGc* self = new(ELeave) CSymTtkGc(aScreen);
	CleanupStack::PushL(self);
	self->ConstructL();
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

void CSymTtkGc::draw_rect(const TtkRect& rect)
{
	const TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
			     rect.br_.x_, rect.br_.y_);
	iGc->DrawRect(sym_rect);
}

void CSymTtkGc::draw_text(const char* text, const TtkRect& rect,
			  bool underline)
{
	TPtrC8 ptr(reinterpret_cast<const unsigned char*>(text));
	HBufC* buffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(ptr);
	CleanupStack::PushL(buffer);
	const TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
			     rect.br_.x_, rect.br_.y_);
	TInt ascent = iFont->AscentInPixels();
	TInt descent = iFont->DescentInPixels();
	TInt offset = (rect.height() + (ascent - descent)) / 2;
	if (underline)
		iGc->SetUnderlineStyle(EUnderlineOn);
	else
		iGc->SetUnderlineStyle(EUnderlineOff);
	iGc->UseFont(iFont);
	iGc->DrawText(*buffer, sym_rect, offset);
	iGc->DiscardFont();
	CleanupStack::PopAndDestroy(buffer);
}

void CSymTtkGc::draw_bitmap(const TtkBitmapInterface& bitmap,
			    const TtkRect& rect)
{
	const TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
			     rect.br_.x_, rect.br_.y_);
	iGc->DrawBitmap(sym_rect,
			dynamic_cast<CSymTtkBitmap>(&bitmap)->Bitmap());
}

void CSymTtkGc::set_clipping_rect(const TtkRect& rect)
{
	const TRect sym_rect(rect.tl_.x_, rect.tl_.y_,
			     rect.br_.x_, rect.br_.y_);
	iGc->SetClippingRect(sym_rect);
}

void CSymTtkGc::set_pen_color(TtkColor color)
{
#ifdef EKA2
	TRgb rgb;
	rgb.SetInternal(color);
#else
	TRgb rgb(color);
#endif
	iGc->SetPenColor(rgb);
}

void CSymTtkGc::set_brush_color(TtkColor color)
{
#ifdef EKA2
	TRgb rgb;
	rgb.SetInternal(color);
#else
	TRgb rgb(color);
#endif
	iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iGc->SetBrushColor(rgb);
}

CWindowGc& CSymTtkGc::Gc() const
{
	return *iGc;
}

CSymTtkGc::CSymTtkGc(CWsScreenDevice& aScreen) : iScreen(aScreen)
{
}

void CSymTtkGc::ConstructL()
{
	User::LeaveIfError(iScreen.CreateContext(iGc));
#ifdef EKA2
	_LIT(KFontName, "Sans MT 936_S60");
#else
	_LIT(KFontName, "CombinedChinesePlain12");
#endif
	const TInt KFontHeight = 200;
	TFontSpec fontSpec(KFontName, KFontHeight);
	User::LeaveIfError(iScreen.GetNearestFontInTwips(iFont, fontSpec));
}
