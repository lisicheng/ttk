/**
 * \file
 * \brief TtkColor枚举定义
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_COLOR_H
#define TTK_COLOR_H

/**
 * \brief 颜色
 */
enum TtkColor {
	kTtkColorRawRed		= 0x00ff0000,
	kTtkColorRawGreen	= 0x0000ff00,
	kTtkColorRawBlue	= 0x000000ff,
	kTtkColorRawAlpha	= 0xff000000,
	kTtkColorBlack		= 0xff000000,
	kTtkColorWhite		= 0xffffffff,
	kTtkColorRed		= 0xffff0000,
	kTtkColorGreen		= 0xff00ff00,
	kTtkColorBlue		= 0xff0000ff,
	kTtkColorTransparent	= 0x00000000
};

#endif /* TTK_COLOR_H */
