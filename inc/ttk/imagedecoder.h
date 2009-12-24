#ifndef TTK_IMAGEDECODERINTERFACE_H
#define TTK_IMAGEDECODERINTERFACE_H

class TtkBitmapInterface;
class TtkImage;

class TtkImageDecoderInterface {
public:
	virtual ~TtkImageDecoderInterface();
public:
	virtual void decode(const char* filename, TtkBitmapInterface*& bitmap,
		       TtkImage& image);
};

#endif /* TTK_IMAGEDECODERINTERFACE_H */
