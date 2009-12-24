/**
 * \file
 * \brief TtkPointer类声明
 * \author 袁野 <yuanyelele@gmail.com>
 * \author 李思诚 <lisicheng2008@gmail.com>
 * \warning 2009 (c) 北京随手互动信息技术有限公司
 */
#ifndef TTK_POINT_H
#define TTK_POINT_H

/**
 * \brief 平面上的点
 *
 * 由整型的x坐标和y坐标定义的二维平面上的点。
 */
class TtkPoint {
public:
	TtkPoint(int x, int y);
public:
	int x_;
	int y_;
};

#endif /* TTK_POINT_H */
