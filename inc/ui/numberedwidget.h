#ifndef NUMBEREDWIDGET_H
#define NUMBEREDWIDGET_H

#include "window/widget.h" // CWidget

class CNumberedWidget : public CWidget
{
public:
	virtual ~CNumberedWidget();
	static CNumberedWidget* NewL(CWsClient& aWsEnv, const CWindow* aParent,
				     const TRect& aRect, TInt aNum);
	static CNumberedWidget* NewLC(CWsClient& aWsEnv, const CWindow* aParent,
				      const TRect& aRect, TInt aNum);
public: /* from CWidget */
	void Draw(const TRect& aRect);
private:
	CNumberedWidget(CWsClient& aWsEnv, TInt aNum);
private:
	TInt iNumber;
};

#endif // NUMBEREDWIDGET_H
