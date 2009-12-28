#include "symttk/bitmap.h"

#include <fbs.h>

CSymTtkBitmap::~CSymTtkBitmap()
{
	delete iBitmap;
}

const CFbsBitmap& CSymTtkBitmap::Bitmap() const
{
	return *iBitmap;
}
