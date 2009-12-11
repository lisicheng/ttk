PROJECT = ttk
TARGETTYPE = exe
UID2 = 100039ce
UID3 = a1986131
SECUREID = a1986131
VENDORID = 0

EPOCSTACKSIZE = 0x5000
CAPABILITY = NONE

RSSTARGET = \
	dist/$(PROJECT)_loc_$(UID3).rsc \
	dist/$(PROJECT)_reg_$(UID3).rsc \
	dist/$(PROJECT)_$(UID3).rsc

SRCFILES = \
	framework/application.cpp \
	framework/appui.cpp \
	framework/document.cpp \
	framework/main.cpp \
	symttk/gc.cpp \
	symttk/redrawer.cpp \
	symttk/window.cpp \
	symttk/wsenv.cpp \
	ttk/common/point.cpp \
	ttk/common/rect.cpp \
	ttk/widget.cpp \
	ui/mainwidget.cpp \
	ui/numberedwidget.cpp

LIBRARY = \
	euser.lib \
	apparc.lib \
	cone.lib \
	eikcore.lib \
	flogger.lib \
	gdi.lib \
	ws32.lib
