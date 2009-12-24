#include "symttk/bitmap.h"

CFbsBitmap::~CFbsBitmap()
{
	delte iBitmap;
}

const CFbsBitmap& CSymTtkBitmap::Bitmap() const
{
	return *iBitmap;
}
