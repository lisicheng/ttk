PROJECT = ttk
TARGETTYPE = exe
UID2 = 100039ce
UID3 = a1986131
SECUREID = a1986131
VENDORID = 0

EPOCSTACKSIZE = 0x5000
CAPABILITY = NONE

RSSFILES = \
	$(PROJECT)_loc.rss \
	$(PROJECT)_reg.rss \
	$(PROJECT).rss

SRCFILES = \
	framework/application.cpp \
	framework/appui.cpp \
	framework/document.cpp \
	framework/main.cpp \
	symttk/gc.cpp \
	symttk/redrawer.cpp \
	symttk/window.cpp \
	symttk/wsenv.cpp \
	symttk/bitmap.cpp \
	ttk/common/point.cpp \
	ttk/common/rect.cpp \
	ttk/widget.cpp \
	ui/label.cpp \
	ui/mainwidget.cpp \
	ui/numberedwidget.cpp

LIBRARY = \
	euser.lib \
	apparc.lib \
	charconv.lib \
	cone.lib \
	eikcore.lib \
	flogger.lib \
	gdi.lib \
	ws32.lib
