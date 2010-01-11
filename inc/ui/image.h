#ifndef TTK_IMAGE_H
#define TTK_IMAGE_H

#include "ttk/widget.h" /* TtkWidget */

class TtkBitmapInterface;

/**
 * \brief 图片
 *
 * 通过指定图片文件名构造，之后由\ref TtkImageDecoderInterface接口负责解码为位图
 * \ref TtkBitmapInterface。图片可以通过\ref TtkGcInterface::draw_bitmap()函数绘
 * 制在窗口指定区域上。如果构造时指定了关联动作，则图片可以获取焦点并响应按键事
 * 件，获得焦点时在图片周围显示虚线边框。
 */
class TtkImage : public TtkWidget {
public:
	virtual ~TtkImage();
	TtkImage(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		 TtkWidget* parent, const char* filename,
		 void (*action)());
public: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& redraw_rect);
	bool focusable() const;
public:
	void decode();
private:
	const char* filename_;
	TtkBitmapInterface* bitmap_;
	void (*action_)();
};

#endif /* TTK_IMAGE_H */
