#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <e32base.h> // CActive
#include <w32std.h> // TKeyEvent

class CWsRedrawer;

class CWsClient : public CActive
{
public:
	virtual ~CWsClient();
public: /* from CActive */
	void DoCancel();
	virtual void RunL() = 0;
public:
	RWsSession& Ws();
	const RWindowGroup& Group() const;
	CWsScreenDevice& Screen();
	CWindowGc& Gc();
public:
	void IssueRequest(); // request an event
	virtual void ConstructMainWindowL(); // main window
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent) = 0;
protected:
	CWsClient();
	void ConstructL();
private:
	RWsSession iWs;
	RWindowGroup iGroup;
	CWsScreenDevice* iScreen;
	CWindowGc* iGc;
	CWsRedrawer* iRedrawer;
	CWidget* aRootWidget; // not owned
};

#endif // WSCLIENT_H
