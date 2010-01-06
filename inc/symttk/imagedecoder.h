#ifndef SYMTTK_IMAGEDECODER_H
#define SYMTTK_IMAGEDECODER_H

#include <e32base.h> /* CBase */
#include "ttk/imagedecoderinterface.h" /* TtkImageDecoderInterface */

class CImageDecoder;
class CSymTtkBitmap;
class TtkImage;

/**
 * \brief Symbian图片解码器
 */
class CSymTtkImageDecoder : public CActive, public TtkImageDecoderInterface {
public:
	virtual ~CSymTtkImageDecoder();
	static CSymTtkImageDecoder* NewL();
	static CSymTtkImageDecoder* NewLC();
public: /* from TtkImageDecoderInterface */
	void decode(const char* filename, TtkBitmapInterface*& bitmap, TtkImage& image);
private:
	CSymTtkImageDecoder();
private: /* from CActive */
	void DoCancel();
	void RunL();
private:
	CImageDecoder* iDecoder;
	TInt iIndex;
	CSymTtkBitmap* iBitmap;
	TtkImage* iImage;
	RTimer iTimer;
	TBool iDecoding;
};

#endif /* SYMTTK_IMAGEDECODER_H */
