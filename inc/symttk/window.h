#ifndef SYMTTK_WINDOW_H
#define SYMTTK_WINDOW_H

#include <e32base.h> // CBase
#include <gdi.h> // TRgb
#include <w32std.h> // RWindow

class TtkWidget;

class CSymTtkWindow : public CBase
{
public:
	virtual ~CSymTtkWindow();
	static CSymTtkWindow* NewL(TtkWidget& aWidget, const TRgb& aColor);
	static CSymTtkWindow* NewLC(TtkWidget& aWidget, const TRgb& aColor);
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

#endif // SYMTTK_WINDOW_H
