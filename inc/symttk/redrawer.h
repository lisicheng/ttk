#ifndef SYMTTK_REDRAWER_H
#define SYMTTK_REDRAWER_H

#include <e32base.h> // CActive

class CWsClient;

class CWsRedrawer : public CActive
{
public:
	~CWsRedrawer();
	static CWsRedrawer* NewL(CWsClient& aWsEnv);
	static CWsRedrawer* NewLC(CWsClient& aWsEnv);
private:
	CWsRedrawer(CWsClient& aWsEnv);
	void ConstructL();
private: /* from CActive */
	void DoCancel();
	void RunL();
private:
	void IssueRequest();
private:
	CWsClient& iWsEnv;
};

#endif // SYMTTK_REDRAWER_H
