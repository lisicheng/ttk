#include "ui/expander.h"
#include "ttk/widget.h"

#include "ttk/common.h"
#include "ttk/common/color.h"
#include "ttk/gcinterface.h"
#include "ttk/windowinterface.h"
#include "ttk/wsenvinterface.h"
#include "ui/label.h"
#include "ui/image.h"

TtkExpander::~TtkExpander()
{
	delete label_;
	delete icon_;
	delete contents_;
}

TtkExpander::TtkExpander(TtkWsEnvInterface& ws_env, const TtkRect& rect,
			 TtkWidget* parent)
	: TtkWidget(ws_env, rect, parent), label_(NULL), icon_(NULL),
	  contents_(NULL), expand_(false)
{
}

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
			TtkRect rect_1_1 = rect();
			rect_1_1.resize(0, 100);
			set_rect(rect_1_1);
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

void TtkExpander::set_rect(const TtkRect& new_rect)
{
	int dx = new_rect.tl_.x_ - rect().tl_.x_;
	int dy = new_rect.tl_.y_ - rect().tl_.y_;
	
	if (label_) {
		TtkRect label_rect = label_->rect();
		label_rect.move(dx, dy);
		label_->set_rect(label_rect);
	}
	if (icon_) {
		/* TODO: move icon_ */
	}
	if (expand_ && contents_) {
	}
}

