#ifndef SYMTTK_WINDOW_H
#define SYMTTK_WINDOW_H

#include <e32base.h> /* CBase */
#include <w32std.h> /* RWindow */
#include "ttk/windowinterface.h" /* TtkWindowInterface */

class TRgb;
class TtkWidget;

/**
 * \brief Symbian窗口
 */
class CSymTtkWindow : public CBase, public TtkWindowInterface
{
public:
	virtual ~CSymTtkWindow();
	static CSymTtkWindow* NewL(TtkWidget& aWidget, const TRgb& aColor);
	static CSymTtkWindow* NewLC(TtkWidget& aWidget, const TRgb& aColor);
public: /* from WindowInterface */
	void redraw(const TtkRect& rect);
public:
	TtkWidget& Widget();
	RWindow& Window();
private:
	CSymTtkWindow(TtkWidget& aWidget);
	void ConstructL(const TRgb& aColor);
private:
	TtkWidget& iWidget;
	RWindow iWindow;
};

#endif /* SYMTTK_WINDOW_H */
