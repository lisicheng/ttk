/**
 * \file
 * \brief TtkImageDecoderInterface接口声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_IMAGEDECODERINTERFACE_H
#define TTK_IMAGEDECODERINTERFACE_H

class TtkBitmapInterface;
class TtkImage;

/**
 * \brief 图片解码器接口
 * 
 * 传入图片文件名，解码为位图\ref TtkBitmapInterface并通知所在控件。支持gif动画
 * 格式的图片。
 */
class TtkImageDecoderInterface {
public:
	virtual ~TtkImageDecoderInterface() {}
public:
	virtual void decode(const char* filename, TtkBitmapInterface*& bitmap,
		       TtkImage& image) = 0;
};

#endif /* TTK_IMAGEDECODERINTERFACE_H */
