#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "ttk/widget.h" // TtkWidget

class CNumberedWidget : public TtkWidget
{
public:
	virtual ~CNumberedWidget();
	static CNumberedWidget* NewL(CSymTtkWsEnv& aWsEnv,
				     const TRect& aRect, TInt aNum,
				     CSymTtkWindow* aParent);
	static CNumberedWidget* NewLC(CSymTtkWsEnv& aWsEnv,
				      const TRect& aRect, TInt aNum,
				      CSymTtkWindow* aParent);
public: /* from TtkWidget */
	void Draw(const TRect& aRect);
private:
	CNumberedWidget(CSymTtkWsEnv& aWsEnv, const TRect& aRect, TInt aNum);
private:
	TInt iNum;
};

#endif // NUMBEREDWIDGET_H
