#ifndef EXAMPLEWSCLIENT_H
#define EXAMPLEWSCLIENT_H

#include "window/wsclient.h" // CWsClient

class CMainWindow;
class CNumberedWindow;

class CExampleWsClient : public CWsClient
{
public:
	virtual ~CExampleWsClient();
	static CExampleWsClient* NewL(const TRect& aRect);
	static CExampleWsClient* NewLC(const TRect& aRect);
private:
	CExampleWsClient(const TRect& aRect);
private: /* from CWsClient */
	void RunL();
	void ConstructMainWindowL();
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
private:
	CMainWindow* iMainWindow;
	CNumberedWindow* iWindow1;
	const TRect& iRect;
};

#endif // EXAMPLEWSCLIENT_H
