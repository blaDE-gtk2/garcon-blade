# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
# 
# Copyright (c) 2013 Nick Schermer <nick@xfce.org>
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
# GNU Library General Public License for more details.
# 
# You should have received a copy of the GNU Library General 
# Public License along with this library; if not, write to the 
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301, USA.

AM_CPPFLAGS = \
	-DGLIB_DISABLE_DEPRECATION_WARNINGS \
	-I$(top_srcdir) \
	-DPOJK_COMPILATION \
	-DPOJK_VERSION_API=\"$(POJK_VERSION_API)\" \
	-DG_LOG_DOMAIN=\"pojk\" \
	-DSYSCONFIGDIR=\"$(sysconfdir)/xdg\" \
	$(PLATFORM_CFLAGS)

lib_LTLIBRARIES = \
	libpojk-gtk3-1.la

libpojk_gtk_headers = \
	pojk-gtk.h \
	pojk-gtk-menu.h

libpojk_gtk_sources = \
	pojk-gtk-menu.c


libpojk_gtk3includedir = \
	$(includedir)/pojk-gtk3-1/pojk-gtk

libpojk_gtk3include_HEADERS = \
	$(libpojk_gtk_headers)

libpojk_gtk3_1_la_SOURCES = \
	$(libpojk_gtk_sources) \
	$(libpojk_gtk_headers)

libpojk_gtk3_1_la_CFLAGS = \
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GTK3_CFLAGS) \
	$(LIBBLADEUTIL_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTHREAD_CFLAGS) \
	$(LIBBLADEUI2_CFLAGS) \
	$(PLATFORM_CFLAGS)

libpojk_gtk3_1_la_LDFLAGS = \
	-no-undefined \
	-export-dynamic \
	-version-info $(POJK_VERINFO) \
	-export-symbols-regex "^[^_].*" \
	$(PLATFORM_LDFLAGS)

libpojk_gtk3_1_la_LIBADD = \
	$(top_builddir)/pojk/libpojk-$(POJK_VERSION_API).la \
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GTK3_LIBS) \
	$(LIBBLADEUTIL_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTHREAD_LIBS) \
	$(LIBBLADEUI2_LIBS)

libpojk_gtk3_1_la_DEPENDENCIES = \
	$(top_builddir)/pojk/libpojk-$(POJK_VERSION_API).la


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pojk-gtk3-1.pc

##
## GTK+ 2 support library
##
if ENABLE_GTK2_LIBRARY

lib_LTLIBRARIES += libpojk-gtk2-1.la

libpojk_gtk2includedir = \
	$(includedir)/pojk-gtk2-1/pojk-gtk

libpojk_gtk2include_HEADERS = \
	$(libpojk_gtk_headers)

libpojk_gtk2_1_la_SOURCES = \
	$(libpojk_gtk_sources) \
	$(libpojk_gtk_headers)

libpojk_gtk2_1_la_CFLAGS = \
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GTK2_CFLAGS) \
	$(LIBBLADEUTIL_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTHREAD_CFLAGS) \
	$(LIBBLADEUI_CFLAGS) \
	$(PLATFORM_CFLAGS)

libpojk_gtk2_1_la_LDFLAGS = \
	-no-undefined \
	-export-dynamic \
	-version-info $(POJK_VERINFO) \
	-export-symbols-regex "^[^_].*" \
	$(PLATFORM_LDFLAGS)

libpojk_gtk2_1_la_LIBADD = \
	$(top_builddir)/pojk/libpojk-$(POJK_VERSION_API).la \
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GTK2_LIBS) \
	$(LIBBLADEUTIL_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTHREAD_LIBS) \
	$(LIBBLADEUI_LIBS)

libpojk_gtk2_1_la_DEPENDENCIES = \
	$(top_builddir)/pojk/libpojk-$(POJK_VERSION_API).la

pkgconfig_DATA += pojk-gtk2-1.pc

endif


# Required for gtk-doc and make distcheck
dist-hook: all
