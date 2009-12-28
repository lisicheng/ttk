/*
 * mainwidget2.h
 *
 *  Created on: 2009-12-15
 *      Author: u
 */

#ifndef MAINWIDGET2_H_
#define MAINWIDGET2_H_

#include "ttk/widget.h" /* TtkWidget */

class TtkList;

class MainWidget2 : public TtkWidget
{
public:
	virtual ~MainWidget2();
	MainWidget2(TtkWsEnvInterface& ws_env, const TtkRect& rect);
private: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& redraw_rect);
private:
	TtkWidget* list_;
};

#endif /* MAINWIDGET2_H_ */
