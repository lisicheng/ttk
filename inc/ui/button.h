#ifndef TTK_BUTTON_H
#define TTK_BUTTON_H

/**
 * \brief 按钮
 *
 * 按钮中包含一个\ref TtkImage和/或一个\ref TtkLabel，具有凸起可点击的视觉效果。
 * 按钮可以获得焦点，获得焦点时具有不同的外观，且响应按键事件，执行指定动作。
 */
class TtkButton : public TtkWidget {
public:
	virtual ~TtkButton();
};

#endif // TTK_BUTTON_H
