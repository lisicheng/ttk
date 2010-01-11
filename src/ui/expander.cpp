#include "ui/expander.h"
#include "ttk/widget.h"

#include "ttk/common.h"
#include "ttk/common/color.h"
#include "ttk/gcinterface.h"
#include "ttk/windowinterface.h"
#include "ttk/wsenvinterface.h"
#include "ui/label.h"
#include "ui/image.h"
#include "common.h"

TtkExpander::~TtkExpander()
{
	delete label_;
	delete icon_;
	delete contents_;
}

TtkExpander::TtkExpander(TtkWsEnvInterface& ws_env, const TtkRect& rect,
			 TtkWidget* parent)
	: TtkWidget(ws_env, rect, parent), label_(NULL), icon_(NULL),
	  contents_(NULL), expand_(false), parent_(parent)
{
}

/**
 * \brief 第二阶段构造函数
 *
 * - 构建标签，区域与折叠页相同（因为初始状态为折叠）
 * - 获取折叠页内容，或创建区域与标题相同的简单控件作为内容
 * - 移动内容到标题下方
 */
void TtkExpander::construct(const char* text, TtkWidget* contents)
{
	label_ = new TtkLabel(ws_env(), rect(), this, text, NULL);
	/* TODO: icon_ */
	if (contents)
		contents_ = contents;
	else
		contents_ = new TtkWidget(ws_env(), rect(), this);
	TtkRect contents_rect(rect().tl_.x_,
			      rect().br_.y_,
			      rect().br_.x_,
			      rect().br_.y_+contents_->rect().height());
	contents_->set_rect(contents_rect);
}

/**
 * \brief 响应重绘事件
 *
 * 当获得焦点时标题为红底色，否则为绿底色。绘制标题栏中的标签和图标，如果状态
 * 为展开则绘制折叠页内容。
 */
void TtkExpander::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(redraw_rect);
	if (has_focus())
		gc.set_brush_color(kTtkColorRed);
	else
		gc.set_brush_color(kTtkColorGreen);
	gc.clear(redraw_rect);
	if (label_)
		label_->handle_redraw_event(redraw_rect);
	if (icon_)
		icon_->handle_redraw_event(redraw_rect);
	if (contents_ && expand_)
		contents_->handle_redraw_event(redraw_rect);
}

/**
 * \brief 响应OK键事件，切换打开/关闭状态
 *
 * -# 改变\ref expand_状态
 * -# \ref set_rect()更改区域
 * -# 调用窗口的重绘函数，重绘父控件区域
 */
void TtkExpander::handle_key_event(TtkKeyEvent& key_event)
{
	switch(key_event) {
	case kTtkKeyOk:
		if (expand_) {
			expand_ = false;
			TtkRect old_rect = rect();
			set_rect(label_->rect());
			window().redraw(old_rect);
		} else {
			expand_ = true;
			TtkRect new_rect = rect();
			new_rect.resize(0, contents_->rect().height());
			set_rect(new_rect);
			LOG("redraw!");
			if (parent_)
				window().redraw(parent_->rect());
			else /* error */
				window().redraw(rect());
		}
		break;
	default:
		break;
	}
}

void TtkExpander::set_focus(bool has_focus)
{
	TtkWidget::set_focus(has_focus);
	label_->set_focus(has_focus);
}

bool TtkExpander::focusable() const
{
	return true;
}

/**
 * \brief 更新占用区域
 *
 * 如果状态为展开
 * - 1 标题宽度适应，高度不变
 * - 2 内容宽高均适应
 *
 * 如果状态为折叠
 * - 1 标题宽高均适应
 * - 2 内容宽度适应，高度不变
 */
void TtkExpander::set_rect(const TtkRect& new_rect)
{
	TtkWidget::set_rect(new_rect);

	if (expand_) {
		if (label_) {
			TtkRect label_rect = new_rect;
			label_rect.br_.y_ = label_rect.tl_.y_ +
					    label_->rect().height();
			label_->set_rect(label_rect);
		}
		/* TODO: move icon_ */
		if (contents_) {
			TtkRect contents_rect = new_rect;
			contents_rect.tl_.y_ = new_rect.tl_.y_+
					       label_->rect().height(),
			contents_->set_rect(contents_rect);
		}
	} else {
		if (label_) {
			label_->set_rect(new_rect);
		}
		/* TODO: move icon_ */
		if (contents_) {
			TtkRect contents_rect(
				new_rect.tl_.x_,
				new_rect.br_.y_,
				new_rect.br_.x_,
				new_rect.br_.y_ + contents_->rect().height()
				);
			contents_->set_rect(contents_rect);
		}
	}
}

