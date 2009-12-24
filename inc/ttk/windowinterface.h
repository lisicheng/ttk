/**
 * \file
 * \brief TtkWindowInterface接口声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_WINDOWINTERFACE_H
#define TTK_WINDOWINTERFACE_H

class TtkRect;

/**
 * \brief 窗口接口
 *
 * 窗口为屏幕上一块指定的区域。每个窗口均与一个控件绑定，该控件的子控件可以借用
 * 根控件拥有的窗口完成屏幕绘制。
 */
class TtkWindowInterface {
public:
	virtual ~TtkWindowInterface() {}
public:
	virtual void redraw(const TtkRect& rect) = 0;
};

#endif /* TTK_WINDOWINTERFACE_H */
