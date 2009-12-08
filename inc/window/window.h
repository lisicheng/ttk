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
	static CWindow* NewL(CWsClient& aWsEnv, const TRect aRect,
			     CWidget& aRootWidget, const TRgb& aColor);
	static CWindow* NewLC(CWsClient& aWsEnv, const TRect aRect,
			      CWidget& aRootWidget, const TRgb& aColor);
public:
	RWindow& Window();
	CWidget& RootWidget();
protected:
	CWindow(CWsClient& aWsEnv, CWidget& aRootWidget);
	void ConstructL(const TRect& aRect, const TRgb& aColor);
private:
	RWindow iWindow; // window server window
	CWsClient& iWsEnv; // client including session and group
	CWidget& iRootWidget;
};

#endif // WINDOW_H
