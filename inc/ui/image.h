#ifndef TTK_IMAGE_H
#define TTK_IMAGE_H

#include "ttk/widget.h" /* TtkWidget */

class TtkImage : public TtkWidget {
public:
	virtual ~TtkImage();
	TtkImage(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		 TtkWindowInterface* window, const char* filename,
		 void (*action)());
public: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& rect);
	bool focusable() const;
public:
	void decode();
private:
	const char* filename_;
	TtkBitmapInterface* bitmap_;
	void (*action_)();
};

#endif /* TTK_IMAGE_H */
