#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "window/widget.h" // CWidget

class CNumberedWidget : public CWidget
{
public:
	virtual ~CNumberedWidget();
	static CNumberedWidget* NewL(CWsClient& aWsEnv,
				     const TRect& aRect, TInt aNum,
				     const CWindow* aParent);
	static CNumberedWidget* NewLC(CWsClient& aWsEnv,
				      const TRect& aRect, TInt aNum,
				      const CWindow* aParent);
public: /* from CWidget */
	void Draw(const TRect& aRect);
private:
	CNumberedWidget(CWsClient& aWsEnv, const TRect& aRect, TInt aNum);
private:
	TInt iNumber;
};

#endif // NUMBEREDWIDGET_H
