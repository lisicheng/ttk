#ifndef TTK_WIDGET_H
#define TTK_WIDGET_H

#include <e32base.h> // CBase
#include <w32std.h> // TKeyEvent

class CSymTtkWsEnv;
class CSymTtkWindow;

class TtkWidget : public CBase
{
public:
	virtual ~TtkWidget();
	static TtkWidget* NewL(CSymTtkWsEnv& ws_client, const TRect& rect,
			     CSymTtkWindow* window);
	static TtkWidget* NewLC(CSymTtkWsEnv& ws_client, const TRect& rect,
			      CSymTtkWindow* window);
public:
	virtual void handle_key_event(TKeyEvent& key_event);
	virtual void handle_pointer_event(TPointerEvent& pointer_event);
	virtual void handle_redraw_event(const TRect& rect);
public:
	CSymTtkWsEnv& ws_env();
	const TRect& rect() const;
	void set_rect(const TRect& rect);
protected:
	TtkWidget(CSymTtkWsEnv& ws_env, const TRect& rect);
	void ConstructL(CSymTtkWindow* window);
protected:
	CSymTtkWindow& window() const;
private:
	CSymTtkWsEnv& ws_env_;
	TRect rect_;
	CSymTtkWindow* window_;
	bool own_window_;
};

#endif // TTK_WIDGET_H
