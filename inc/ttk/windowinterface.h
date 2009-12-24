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
 */
class TtkWindowInterface {
public:
	virtual ~TtkWindowInterface() {}
public:
	virtual void redraw(const TtkRect& rect) = 0;
};

#endif /* TTK_WINDOWINTERFACE_H */
