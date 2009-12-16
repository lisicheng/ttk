#include "ui/image.h"

TtkImage::~TtkImage()
{
}

TtkImage::TtkImage(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		   TtkWindowInterface* window, const char* filename)
		: TtkWidget(ws_env, rect, window), filename_(filename),
{
}

void TtkImage::handle_redraw_event(const TtkRect& rect)
{
}
