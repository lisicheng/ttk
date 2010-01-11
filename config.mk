PROJECT = ttk
TARGETTYPE = exe
ifeq ($(TARGETTYPE), exe)
UID1 = 1000007a
UID2 = 00000000
else
UID1 = 10000079
UID2 = 1000008d
endif
UID3 = a1986131
SECUREID = a1986131
VENDORID = 0

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
	symttk/imagedecoder.cpp \
	ttk/common/point.cpp \
	ttk/common/rect.cpp \
	ttk/widget.cpp \
	ui/label.cpp \
	ui/list.cpp \
	ui/expander.cpp \
	ui/image.cpp \
	ui/label.cpp \
	ui/scrollbar.cpp \
	example/mainwidget.cpp \
	example/mainwidget2.cpp \
	example/numberedwidget.cpp

LIBRARY = \
	euser.lib \
	apparc.lib \
	avkon.lib \
	charconv.lib \
	cone.lib \
	eikcore.lib \
	fbscli.lib \
	flogger.lib \
	gdi.lib \
	imageconversion.lib \
	ws32.lib
