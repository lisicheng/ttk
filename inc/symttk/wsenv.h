#ifndef SYMTTK_WSENV_H 
#define SYMTTK_WSENV_H

#include <e32base.h> // CActive
#include <w32std.h> // RWsSession

class CWsRedrawer;
class CWidget;

class CWsClient : public CActive
{
public:
	virtual ~CWsClient();
	static CWsClient* NewL(const TRect& aRect);
	static CWsClient* NewLC(const TRect& aRect);
public:
	RWsSession& Ws();
	const RWindowGroup& Group() const;
	CWsScreenDevice& Screen() const;
	CWindowGc& Gc() const;
private:
	CWsClient();
	void ConstructL(const TRect& aRect);
private: /* from CActive */
	void DoCancel();
	void RunL();
private:
	void IssueRequest();
private:
	RWsSession iWs;
	RWindowGroup iGroup;
	CWsScreenDevice* iScreen;
	CWindowGc* iGc;
	const CWsRedrawer* iRedrawer;
	CWidget* iRootWidget;
};

#endif // SYMTTK_WSENV_H
