#include "ui/image.h"

TtkImage::~TtkImage()
{
	delete bitmap_
}

TtkImage::TtkImage(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		   TtkWindowInterface* window, const char* filename)
		: TtkWidget(ws_env, rect, window), filename_(filename),
		  action_(action)
{
}

void TtkImage::handle_key_event(TtkKeyEvent& key_event)
{
	if (key_event == kTtkKeyOk) {
		if (action_)
			action_();
	}
}

void TtkImage::handle_redraw_event(const TtkRect& redraw_rect)
{
	TtkGcInterface& gc = ws_env().gc();
	gc.set_clipping_rect(redraw_rect);

	TtkRect image_rect(rect());
	TtkRect bitmap_rect(image_rect.tl_.x_ + 1,
			    image_rect.tl_.y_ + 1,
			    image_rect.br_.x_ - 1,
			    image_rect.br_.y_ - 1);
	gc.clear(image_rect);
	if (has_focus()) {
		gc.set_pen_color(kTtkColorBlue);
		gc.draw_rect(image_rect);
	}
	if (bitmap_)
		gc.draw_bitmap(*bitmap_, bitmap_rect);
}

bool TtkImage::focusable() const
{
	if (action_)
		return true;
	else
		return false;
}

void TtkImage::decode()
{
	ws_env().image_decoder().decode(filename_, &bitmap_, *this);
}
