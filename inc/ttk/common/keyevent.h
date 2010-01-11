/**
 * \file
 * \brief TtkKeyEvent枚举定义
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_KEYEVENT_H
#define TTK_KEYEVENT_H

/**
 * \breif 按键事件
 *
 * 按键事件枚举定义，每个枚举值定义键盘上的一个按键。
 */
enum TtkKeyEvent {
	kTtkKeyUp,
	kTtkKeyDown,
	kTtkKeyLeft,
	kTtkKeyRight,
	kTtkKeyOk,
	kTtkKeyUnknown
};

#endif /* TTK_KEYEVENT_H */
