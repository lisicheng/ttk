#ifndef SYMTTK_WSENV_H
#define SYMTTK_WSENV_H

#include <e32base.h> /* CActive */
#include <w32std.h> /* RWsSession */
#include "ttk/wsenvinterface.h" /* TtkWsEnvInterface */

class CSymTtkGc;
class CSymTtkRedrawer;
class TtkWidget;

/**
 * \brief Symbian窗口管理器环境
 */
class CSymTtkWsEnv : public CActive, public TtkWsEnvInterface
{
public:
	virtual ~CSymTtkWsEnv();
	static CSymTtkWsEnv* NewL(const TRect& aRect);
	static CSymTtkWsEnv* NewLC(const TRect& aRect);
public: /* from WsEnvInterface */
	TtkWindowInterface* new_window(TtkWidget& widget, TtkColor color) const;
	TtkGcInterface& gc() const;
public:
	RWsSession& Ws();
	const RWindowGroup& Group() const;
	CWsScreenDevice& Screen() const;
	CSymTtkGc& Gc() const;
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
	CSymTtkGc* iGc;
	const CSymTtkRedrawer* iRedrawer;
	TtkWidget* iRootWidget;
};

#endif /* SYMTTK_WSENV_H */
