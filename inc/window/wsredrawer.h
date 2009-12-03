#ifndef WSREDRAWER_H
#define WSREDRAWER_H

#include <e32base.h> // CActive

class CWsClient;

class CWsRedrawer : public CActive
{
public:
	~CWsRedrawer();
	static CWsRedrawer* NewL(CWsClient& aClient);
	static CWsRedrawer* NewLC(CWsClient& aClient);
public:
	void IssueRequest();
public:
	void DoCancel();
	void RunL();
private:
	CWsRedrawer(CWsClient& aClient);
	void ConstructL();
private:
	CWsClient& iClient;
};

#endif // WSREDRAWER_H
