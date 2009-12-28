#ifndef SYMTTK_IMAGEDECODER_H
#define SYMTTK_IMAGEDECODER_H

#include <e32base.h> /* CBase */
#include "ttk/imagedecoderinterface.h" /* TtkImageDecoderInterface */

/**
 * \brief Symbian图片解码器
 */
class CSymTtkImageDecoder : public CBase, public TtkImageDecoderInterface {
public:
	virtual ~CSymTtkImageDecoder();
	static CSymTtkImageDecoder* NewL();
	static CSymTtkImageDecoder* NewLC();
public: /* from TtkImageDecoderInterface */
	void decode(const char* filename, TtkBitmapInterface*& bitmap, TtkImage& image);

};

#endif /* SYMTTK_IMAGEDECODER_H */
