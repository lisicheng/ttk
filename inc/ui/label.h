#ifndef TTK_LABEL_H
#define TTK_LABEL_H

class TtkLabel : public TtkWidget {
public:
	virtual ~TtkLabel();
	TtkLabel(TtkWsEnvInterface& ws_env, const TtkRect& rect,
		 TtkWindowInterface* window, const char* text,
		 void (*action)());
public: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& rect);
	bool focusable() const;
private:
	const char* text_;
	void (*action_)();
}

#endif // TTK_LABEL_H
