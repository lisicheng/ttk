#ifndef TTK_WSENVINTERFACE_H
#define TTK_WSENVINTERFACE_H

#include "ttk/common/color.h" // TtkColor

class TtkGcInterface;
class TtkWidget;
class TtkWindowInterface;

class TtkWsEnvInterface {
public:
	virtual ~TtkWsEnvInterface() {}
public:
	virtual TtkWindowInterface* new_window(TtkWidget& widget,
					       TtkColor color) const = 0;
	virtual TtkGcInterface& gc() const = 0;
};

#endif // TTK_WSENVINTERFACE_H
