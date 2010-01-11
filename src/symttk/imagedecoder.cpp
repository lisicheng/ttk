#include "symttk/bitmap.h"
#include "symttk/imagedecoder.h"
#include "ui/image.h"
#include <coemain.h>
#include <gdi.h>
#include <imageconversion.h>
#include <utf.h>

CSymTtkImageDecoder::~CSymTtkImageDecoder()
{
	Cancel();
	iTimer.Close();
	delete iDecoder;
	delete iBitmap;
}

CSymTtkImageDecoder* CSymTtkImageDecoder::NewL()
{
	CSymTtkImageDecoder* self = CSymTtkImageDecoder::NewLC();
	CleanupStack::Pop(self);
	return self;
}

CSymTtkImageDecoder* CSymTtkImageDecoder::NewLC()
{
	CSymTtkImageDecoder* self = new(ELeave) CSymTtkImageDecoder();
	CleanupStack::PushL(self);
	return self;
}

void CSymTtkImageDecoder::decode(const char* filename,
				 TtkBitmapInterface*& bitmap, TtkImage& image)
{
	_LIT8(KGifMimeType, "image/gif");
	CActiveScheduler::Add(this);
	TPtrC8 ptr(reinterpret_cast<const unsigned char*>(filename));
	HBufC* buffer = CnvUtfConverter::ConvertToUnicodeFromUtf8L(ptr);
	CleanupStack::PushL(buffer);
	iDecoder = CImageDecoder::FileNewL(CCoeEnv::Static()->FsSession(),
			*buffer, KGifMimeType);
	CleanupStack::PopAndDestroy(buffer);
	iTimer.CreateLocal();
	iImage = &image;
	RunL();
}

CSymTtkImageDecoder::CSymTtkImageDecoder()
	: CActive(EPriorityStandard), iIndex(-1)
{
}

void CSymTtkImageDecoder::DoCancel()
{
	iDecoder->Cancel();
	iTimer.Cancel();
}

void CSymTtkImageDecoder::RunL()
{
	const TInt KFrameTimeOut = 1000 * 1000;
	Cancel();
	if (iDecoding) {
		iDecoding = EFalse;
		iImage->handle_redraw_event(iImage->rect());
		iTimer.After(iStatus, KFrameTimeOut);
	} else {
		iDecoding = ETrue;
		iIndex++;
		if (iIndex >= iDecoder->FrameCount())
			iIndex = 0;
		delete iBitmap;
		iBitmap = NULL;
		iBitmap = CSymTtkBitmap::NewL(iImage->rect().width(),
					      iImage->rect().height());
		iDecoder->Convert(&iStatus, iBitmap->Bitmap(), iIndex);
	}
	SetActive();
}
