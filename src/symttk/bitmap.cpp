#include "symttk/bitmap.h"

#include <fbs.h>

CSymTtkBitmap::~CSymTtkBitmap()
{
	delete iBitmap;
}

CSymTtkBitmap* CSymTtkBitmap::NewL(TInt aWidth, TInt aHeight)
{
	CSymTtkBitmap* self = CSymTtkBitmap::NewLC(aWidth, aHeight);
	CleanupStack::Pop(self);
	return self;
}

CSymTtkBitmap* CSymTtkBitmap::NewLC(TInt aWidth, TInt aHeight)
{
	CSymTtkBitmap* self = new(ELeave) CSymTtkBitmap();
	CleanupStack::PushL(self);
	self->ConstructL(aWidth, aHeight);
	return self;
}

int CSymTtkBitmap::width() const
{
	return iWidth;
}

int CSymTtkBitmap::height() const
{
	return iHeight;
}

CFbsBitmap& CSymTtkBitmap::Bitmap() const
{
	return *iBitmap;
}

void CSymTtkBitmap::ConstructL(TInt aWidth, TInt aHeight)
{
	User::LeaveIfError(iBitmap->Create(TSize(aWidth, aHeight), EColor256));
	iWidth = aWidth;
	iHeight = aHeight;
}

