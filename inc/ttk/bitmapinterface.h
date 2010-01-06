/**
 * \file
 * \brief TtkBitmapInterface接口声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_BITMAPINTERFACE_H
#define TTK_BITMAPINTERFACE_H

/**
 * \brief 位图接口
 *
 * 可由图形上下文直接绘制在屏幕上的位图
 */
class TtkBitmapInterface {
public:
	virtual ~TtkBitmapInterface() {}
public:
	virtual int width() const = 0;
	virtual int height() const = 0;
};

#endif /* TTK_BITMAPINTERFACE_H */
