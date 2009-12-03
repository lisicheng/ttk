#ifndef WSREDRAWER_H
#define WSREDRAWER_H

#include <e32base.h> // CActive

class CWsClient;

class CWsRedrawer : public CActive
{
public:
	// construct/destruct
	CWsRedrawer();
	void ConstructL(CWsClient* aClient);
	~CWsRedrawer();
	// drawing
	void IssueRequest();
	void DoCancel();
	void RunL();
protected:
	CWsClient* iClient;
};

#endif // WSREDRAWER_H
