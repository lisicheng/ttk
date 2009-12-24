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

/**
 * \brief Symbian位图
 */
class CSymTtkBitmap : public CBase, public TtkBitmapInterface {
public:
	virtual ~CSymTtkBitmap();
	static CSymTtkGc* NewL();
	static CSymTtkGc* NewLC();
};

#endif /* SYMTTK_BITMAP_H */
