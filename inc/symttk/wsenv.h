#ifndef SYMTTK_WSENV_H
#define SYMTTK_WSENV_H

#include <e32base.h> // CActive
#include <w32std.h> // RWsSession

class CSymTtkRedrawer;
class TtkWidget;

class CSymTtkWsEnv : public CActive
{
public:
	virtual ~CSymTtkWsEnv();
	static CSymTtkWsEnv* NewL(const TRect& aRect);
	static CSymTtkWsEnv* NewLC(const TRect& aRect);
public:
	RWsSession& Ws();
	const RWindowGroup& Group() const;
	CWsScreenDevice& Screen() const;
	CWindowGc& Gc() const;
private:
	CSymTtkWsEnv();
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
	const CSymTtkRedrawer* iRedrawer;
	TtkWidget* iRootWidget;
};

#endif // SYMTTK_WSENV_H
