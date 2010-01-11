/**
 * \file
 * \brief SymTtkBitmap类声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef SYMTTK_BITMAP_H
#define SYMTTK_BITMAP_H

#include <e32base.h> /* CBase */
#include "ttk/bitmapinterface.h" /* TtkBitmapInterface */

class CFbsBitmap;

/**
 * \brief Symbian位图
 */
class CSymTtkBitmap : public CBase, public TtkBitmapInterface {
public:
	virtual ~CSymTtkBitmap();
	static CSymTtkBitmap* NewL(TInt aWidth, TInt aHeight);
	static CSymTtkBitmap* NewLC(TInt aWidth, TInt aHeight);
public: /* from TtkBitmapInterface */
	int width() const;
	int height() const;
public:
	CFbsBitmap& Bitmap() const;
private:
	void ConstructL(TInt aWidth, TInt aHeight);
private:
	CFbsBitmap* iBitmap;
	TInt iWidth;
	TInt iHeight;
};

#endif /* SYMTTK_BITMAP_H */
