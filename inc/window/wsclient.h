#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <e32base.h> // CActive
#include <w32std.h> // TKeyEvent

class CWsRedrawer;
class CWidget;

class CWsClient : public CActive
{
public:
	virtual ~CWsClient();
	static CWsClient* NewL(const TRect& aRect);
	static CWsClient* NewLC(const TRect& aRect);
public: /* from CActive */
	void DoCancel();
	void RunL();
public:
	RWsSession& Ws();
	const RWindowGroup& Group() const;
	CWsScreenDevice& Screen();
	CWindowGc& Gc();
public:
	void IssueRequest(); // request an event
	void HandleKeyEventL(TKeyEvent& aKeyEvent);
protected:
	CWsClient();
	void ConstructL(const TRect& aRect);
private:
	RWsSession iWs;
	RWindowGroup iGroup;
	CWsScreenDevice* iScreen;
	CWindowGc* iGc;
	CWsRedrawer* iRedrawer;
	CWidget* iRootWidget;
};

#endif // WSCLIENT_H
