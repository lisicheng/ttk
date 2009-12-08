#ifndef WINDOW_H
#define WINDOW_H

#include <e32base.h> // CBase
#include <w32std.h> // TPointerEvent

class CWsClient;

class CWindow : public CBase
{
public:
	virtual ~CWindow();
public:
	RWindow& Window();
protected:
	CWindow(CWsClient& aClient);
	void ConstructL(const TRect& aRect, const TRgb& aColor);
private:
	RWindow iWindow; // window server window
	CWsClient& iClient; // client including session and group
};

#endif // WINDOW_H
