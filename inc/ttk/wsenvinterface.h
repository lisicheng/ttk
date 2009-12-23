/**
 * \file
 * \brief TtkWsEnvInterface接口声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_WSENVINTERFACE_H
#define TTK_WSENVINTERFACE_H

#include "ttk/common/color.h" /* TtkColor */

class TtkGcInterface;
class TtkWidget;
class TtkWindowInterface;

/**
 * \brief 窗口管理器环境接口
 */
class TtkWsEnvInterface {
public:
	virtual ~TtkWsEnvInterface() {}
public:
	virtual TtkWindowInterface* new_window(TtkWidget& widget,
					       TtkColor color) const = 0;
	virtual TtkGcInterface& gc() const = 0;
};

#endif /* TTK_WSENVINTERFACE_H */
