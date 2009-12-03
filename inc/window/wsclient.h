#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <e32base.h> // CActive
#include <w32std.h> // TKeyEvent

class CWsRedrawer;
class CWindow;

class CWsClient : public CActive
{
public:
	virtual ~CWsClient();
public: /* from CActive */
	void DoCancel();
	virtual void RunL() = 0;
public:
	void IssueRequest(); // request an event
	virtual void ConstructMainWindowL(); // main window
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent) = 0;
protected:
	CWsClient();
	void ConstructL();
protected:
	CWsScreenDevice* iScreen;
	CWsRedrawer* iRedrawer;
	RWsSession iWs;
private:
	RWindowGroup iGroup;
	CWindowGc* iGc;
	friend class CWsRedrawer; // needs to get at session
	friend class CWindow; // needs to get at session
};

#endif // WSCLIENT_H

