#ifndef TTK_IMAGE_H
#define TTK_IMAGE_H

#include "ttk/widget.h" /* TtkWidget */

class TtkImage : public TtkWidget {
public:
	virtual ~TtkImage();
	TtkImage(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		 TtkWindowInterface* window, const char* filename);
public: /* from TtkWidget */
	void handle_redraw_event(const TtkRect& rect);
private:
	TtkBitmapInterface* bitmap_;
};

#endif /* TTK_IMAGE_H */
