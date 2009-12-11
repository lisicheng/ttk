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
	void set_clipping_rect(const TtkRect& rect);
	void set_pen_color(TtkColor color);
public:
	CWindowGc& Gc() const;
private:
	void ConstructL(CWsScreenDevice& aScreen);
private:
	CWindowGc* iGc;
};

#endif /* SYMTTK_GC_H */

