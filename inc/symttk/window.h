#ifndef WINDOW_H
#define WINDOW_H

#include <e32base.h> // CBase
#include <gdi.h> // TRgb
#include <w32std.h> // RWindow

class CWsClient;
class CWidget;

class CWindow : public CBase
{
public:
	virtual ~CWindow();
	static CWindow* NewL(CWidget& aWidget, const TRgb& aColor);
	static CWindow* NewLC(CWidget& aWidget, const TRgb& aColor);
public:
	CWidget& Widget();
	RWindow& Window();
protected:
	CWindow(CWidget& aWidget);
	void ConstructL(const TRgb& aColor);
private:
	CWidget& iWidget;
	RWindow iWindow;
};

#endif // WINDOW_H
