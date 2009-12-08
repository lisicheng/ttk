#ifndef WSREDRAWER_H
#define WSREDRAWER_H

#include <e32base.h> // CActive

class CWsClient;

class CWsRedrawer : public CActive
{
public:
	~CWsRedrawer();
	static CWsRedrawer* NewL(CWsClient& aWsEnv);
	static CWsRedrawer* NewLC(CWsClient& aWsEnv);
public: /* from CActive */
	void DoCancel();
	void RunL();
public:
	void IssueRequest();
private:
	CWsRedrawer(CWsClient& aWsEnv);
	void ConstructL();
private:
	CWsClient& iWsEnv;
};

#endif // WSREDRAWER_H
