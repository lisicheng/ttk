#ifndef SYMTTK_GC_H
#define SYMTTK_GC_H

#include <w32std.h> /* CWindowGc */
#include "ttk/gcinterface.h" /* TtkGcInterface */

class CWsScreenDevice;

class CSymTtkGc : public CBase, public TtkGcInterface {
public:
	virtual ~CSymTtkGc();
	static CSymTtkGc* NewL(CWsScreenDevice& aScreen);
	static CSymTtkGc* NewLC(CWsScreenDevice& aScreen);
public: /* from TtkGcInterface */
	void clear(const TtkRect& rect);
	void draw_line(const TtkPoint& p1, const TtkPoint& p2);
	void draw_rect(const TtkRect& rect);
	void draw_text(const unsigned char* text, const TtkRect& rect,
		       bool underline);
	void set_clipping_rect(const TtkRect& rect);
	void set_pen_color(TtkColor color);
	void set_brush_color(TtkColor color);
public:
	CWindowGc& Gc() const;
private:
	CSymTtkGc(CWsScreenDevice& aScreen);
	void ConstructL();
private:
	CWindowGc* iGc;
	CWsScreenDevice& iScreen;
	CFont* iFont;
};

#endif /* SYMTTK_GC_H */

