#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <e32base.h> // CActive
#include <w32std.h> // TKeyEvent

class CWsClient;

class CWidget : public CBase
{
public:
	virtual ~CWidget();
public:
	virtual void ConstructMainWindowL(); // main window
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent) = 0;
protected:
	CWidget(CWsClient& aWsEnv);
	void ConstructL();
private:
	CWsClient& iWsEnv;
};

#endif // WSCLIENT_H
