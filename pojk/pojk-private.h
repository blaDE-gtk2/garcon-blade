/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2009 Jannis Pohlmann <jannis@xfce.org>
 * Copyright (c) 2009 Nick Schermer <nick@xfce.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#if !defined(POJK_INSIDE_POJK_H) && !defined(POJK_COMPILATION)
#error "Only <pojk/pojk.h> can be included directly. This file may disappear or change contents."
#endif

#ifndef __POJK_PRIVATE_H__
#define __POJK_PRIVATE_H__

G_BEGIN_DECLS

/* Macro for new g_?list_free_full function */
#if GLIB_CHECK_VERSION (2, 28, 0)
#define _pojk_g_slist_free_full(list,free_func) \
  g_slist_free_full (list, (GDestroyNotify) free_func)
#define _pojk_g_list_free_full(list,free_func) \
  g_list_free_full (list, (GDestroyNotify) free_func)
#else
#define _pojk_g_slist_free_full(list,free_func) G_STMT_START { \
  g_slist_foreach (list, (GFunc) free_func, NULL); \
  g_slist_free (list); } G_STMT_END
#define _pojk_g_list_free_full(list,free_func) G_STMT_START { \
  g_list_foreach (list, (GFunc) free_func, NULL); \
  g_list_free (list); } G_STMT_END
#endif

/* if XDG_MENU_PREFIX is not set, default to "xfce-" so pojk doesn't
 * break when xfce is not started with startxfce4 */
#define POJK_DEFAULT_MENU_PREFIX "xfce-"

GFile    *_pojk_file_new_for_unknown_input    (const gchar *path,
                                                 GFile       *parent);

GFile    *_pojk_file_new_relative_to_file     (const gchar *path,
                                                 GFile       *file);

gchar    *_pojk_file_get_uri_relative_to_file (const gchar *path,
                                                 GFile       *file);

G_END_DECLS

#endif /* !__POJK_PRIVATE_H__ */
