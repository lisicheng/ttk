PROJECT = scroll
TARGETTYPE = app
UID2 = 100039ce
UID3 = 100098e6

RSSTARGET = \
	dist/$(PROJECT).rsc

SRCFILES = \
	framework/main.cpp \
	framework/application.cpp \
	framework/document.cpp \
	framework/appui.cpp \
	window/window.cpp \
	window/wsclient.cpp \
	window/wsredrawer.cpp \
	window/widget.cpp \
	ui/examplewsclient.cpp \
	ui/mainwindow.cpp \
	ui/numberedwindow.cpp

LIBRARY = \
	apparc.lib \
	cone.lib \
	eikcore.lib \
	euser.lib \
	gdi.lib \
	ws32.lib
