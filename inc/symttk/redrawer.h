#ifndef SYMTTK_REDRAWER_H
#define SYMTTK_REDRAWER_H

#include <e32base.h> // CActive

class CSymTtkWsEnv;

class CSymTtkRedrawer : public CActive
{
public:
	~CSymTtkRedrawer();
	static CSymTtkRedrawer* NewL(CSymTtkWsEnv& aWsEnv);
	static CSymTtkRedrawer* NewLC(CSymTtkWsEnv& aWsEnv);
private:
	CSymTtkRedrawer(CSymTtkWsEnv& aWsEnv);
	void ConstructL();
private: /* from CActive */
	void DoCancel();
	void RunL();
private:
	void IssueRequest();
private:
	CSymTtkWsEnv& iWsEnv;
};

#endif // SYMTTK_REDRAWER_H
