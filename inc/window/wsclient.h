#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <e32base.h> // CActive
#include <w32std.h> // TKeyEvent

class CWsRedrawer;
class CWindow;

class CWsClient : public CActive
{
public:
	~CWsClient();
public:
	void DoCancel();
	virtual void RunL() = 0;
public:
	// active object protocol
	void IssueRequest(); // request an event
	// main window
	virtual void ConstructMainWindowL();
	virtual void HandleKeyEventL(TKeyEvent& aKeyEvent) = 0;
protected:
	CWsClient();
	void ConstructL();
protected:
	CWsScreenDevice* iScreen;
	CWsRedrawer* iRedrawer;
	RWsSession iWs;
	//TWsEvent iWsEvent;
private:
	RWindowGroup iGroup;
	CWindowGc* iGc;
	friend class CWsRedrawer; // needs to get at session
	friend class CWindow; // needs to get at session
};

#endif // WSCLIENT_H

