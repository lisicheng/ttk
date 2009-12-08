#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "window/widget.h" // CWidget

class CNumberedWidget : public CWidget
{
public:
	virtual ~CNumberedWidget();
	CNumberedWidget* NewL(CWsClient& aWsEnv, const CWidget* aParent,
			      const TRect* aRect, TInt aNum)
	CNumberedWidget* NewLC(CWsClient& aWsEnv, const CWidget* aParent,
			       const TRect* aRect, TInt aNum)
public: /* from CWidget */
	void Draw(const TRect& aRect);
private:
	CNumberedWidget(CWsClient& aWsEnv, TInt aNum);
}

#endif // NUMBEREDWIDGET_H
