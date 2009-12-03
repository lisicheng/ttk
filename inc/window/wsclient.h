#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <e32base.h> // CActive
#include <w32std.h> // TKeyEvent

class CWsRedrawer;
class CWindow;

class CWsClient : public CActive
{
public:
	void ConstructL();
	~CWsClient();
	// main window
	virtual void ConstructMainWindowL();
	// terminate cleanly
	void Exit();
	// active object protocol
	void IssueRequest(); // request an event
	void DoCancel(); // cancel the request
	virtual void RunL() = 0; // handle completed request
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent) = 0;
protected:
	//construct
	CWsClient();
	CWsScreenDevice* iScreen;
	CWsRedrawer* iRedrawer;
	RWsSession iWs;
	TWsEvent iWsEvent;
private:
	RWindowGroup iGroup;
	CWindowGc* iGc;
	friend class CWsRedrawer; // needs to get at session
	friend class CWindow; // needs to get at session
};

#endif // WSCLIENT_H

