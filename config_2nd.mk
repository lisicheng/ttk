PROJECT = ttk
TARGETTYPE = app
UID2 = 100039ce
UID3 = 100098e6

RSSTARGET = \
	dist/$(PROJECT)_caption.rsc \
	dist/$(PROJECT).rsc

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
	ui/label.cpp \
	ui/mainwidget.cpp \
	ui/numberedwidget.cpp

LIBRARY = \
	apparc.lib \
	charconv.lib \
	cone.lib \
	eikcore.lib \
	euser.lib \
	flogger.lib \
	gdi.lib \
	ws32.lib
