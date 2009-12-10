#ifndef SYMTTK_GC_H
#define SYMTTK_GC_H

#include <w32std.h> // CWindowGc
#include "ttk/gcinterface.h" // TtkGcInterface

class CWsScreenDevice;

class CSymTtkGc : public CWindowGc, public TtkGcInterface {
public: /* from TtkGcInterface */
	void clear(const TtkRect& rect);
private: /* from CWindowGc */
	CSymTtkGc(CWsScreenDevice* aDevice);
};

#endif // SYMTTK_GC_H

