# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
# 
# Copyright (c) 2007-2010 Jannis Pohlmann <jannis@xfce.org>
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

AM_CPPFLAGS = 								\
	-DGLIB_DISABLE_DEPRECATION_WARNINGS \
	-I$(top_srcdir)							\
	-DPOJK_COMPILATION						\
	-DPOJK_VERSION_API=\"$(POJK_VERSION_API)\"			\
	-DG_LOG_DOMAIN=\"pojk\"					\
	-DSYSCONFIGDIR=\"$(sysconfdir)/xdg\"				\
	$(PLATFORM_CFLAGS)

lib_LTLIBRARIES = 							\
	libpojk-1.la

libpojk_built_public_sources =					\
	pojk-marshal.h

libpojk_built_sources =						\
	$(libpojk_built_public_sources)				\
	pojk-marshal.c

libpojk_headers =							\
	pojk.h							\
	pojk-config.h							\
	pojk-marshal.h						\
	pojk-menu-element.h						\
	pojk-menu-separator.h						\
	pojk-menu-directory.h						\
	pojk-menu-item-action.h						\
	pojk-menu-item-pool.h						\
	pojk-menu-item-cache.h					\
	pojk-environment.h						\
	pojk-menu.h							\
	pojk-menu-item.h						\
	pojk-menu-node.h						\
	pojk-menu-tree-provider.h					\
	pojk-menu-merger.h						\
	pojk-menu-parser.h

libpojk_sources =							\
	pojk-config.c							\
	pojk-marshal.c						\
	pojk-menu-element.c						\
	pojk-menu-separator.c						\
	pojk-menu-directory.c						\
	pojk-menu-item-action.c						\
	pojk-menu-item-pool.c						\
	pojk-menu-item-cache.c					\
	pojk-environment.c						\
	pojk-menu.c							\
	pojk-menu-item.c						\
	pojk-menu-node.c						\
	pojk-menu-tree-provider.c					\
	pojk-menu-merger.c						\
	pojk-menu-parser.c						\
	pojk-private.c						\
	pojk-private.h

libpojkincludedir = $(includedir)/pojk-1/pojk

libpojkinclude_HEADERS =						\
	$(libpojk_headers)

libpojk_1_la_SOURCES =						\
	$(libpojk_sources)						\
	$(libpojk_headers)

libpojk_1_la_CFLAGS = 						\
	$(GIO_CFLAGS)							\
	$(GLIB_CFLAGS)							\
	$(LIBBLADEUTIL_CFLAGS)						\
	$(GOBJECT_CFLAGS)						\
	$(GTHREAD_CFLAGS)						\
	$(PLATFORM_CFLAGS)

libpojk_1_la_LDFLAGS =						\
	-no-undefined							\
	-export-dynamic							\
	-version-info $(POJK_VERINFO)					\
	-export-symbols-regex "^[^_].*"					\
	$(PLATFORM_LDFLAGS)

libpojk_1_la_LIBADD = 						\
	$(GIO_LIBS)							\
	$(GLIB_LIBS)							\
	$(LIBBLADEUTIL_LIBS)						\
	$(GOBJECT_LIBS)							\
	$(GTHREAD_LIBS)

EXTRA_DIST =								\
	pojk-config.h.in						\
	pojk-marshal.list

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pojk-1.pc

DISTCLEANFILES =							\
	stamp-pojk-marshal.h						\
	pojk-config.h							\
	$(libpojk_built_sources)

BUILT_SOURCES =								\
	$(libpojk_built_sources)

pojk-marshal.h: stamp-pojk-marshal.h
	@true

stamp-pojk-marshal.h: pojk-marshal.list Makefile
	$(AM_V_GEN) ( \
	  cd $(top_builddir)/pojk \
	  && echo "#ifndef __POJK_MARSHAL_H__" > xgen-emh \
	  && echo "#define __POJK_MARSHAL_H__" >> xgen-emh \
	  && ( glib-genmarshal \
	  	--prefix=pojk_marshal \
	  	--header $(srcdir)/pojk-marshal.list ) >> xgen-emh \
	  && echo "#endif /* !__POJK_MARSHAL_H__ */" >> xgen-emh \
	  && ( cmp -s xgen-emh pojk-marshal.h \
	  	|| cp xgen-emh pojk-marshal.h ) \
	  && rm -f xgen-emh \
	  && echo timestamp > $(@F) \
	)

pojk-marshal.c: pojk-marshal.list Makefile
	$(AM_V_GEN) ( \
	  cd $(top_builddir)/pojk \
	  && echo "#include <pojk/pojk-marshal.h>" > xgen-emc \
	  && ( glib-genmarshal \
	  	--prefix=pojk_marshal \
	  	--body $(srcdir)/pojk-marshal.list ) >> xgen-emc \
	  && cp xgen-emc pojk-marshal.c \
	  && rm -f xgen-emc \
	)

# Required for gtk-doc and make distcheck
dist-hook: all
