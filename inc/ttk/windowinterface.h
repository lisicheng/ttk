#ifndef TTK_WINDOWINTERFACE_H
#define TTK_WINDOWINTERFACE_H

class TtkRect;

class TtkWindowInterface {
public:
	virtual ~TtkWindowInterface() {}
public:
	virtual void redraw(const TtkRect& rect) = 0;
};

#endif // TTK_WINDOWINTERFACE_H
