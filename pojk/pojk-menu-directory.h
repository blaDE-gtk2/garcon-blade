/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2007-2009 Jannis Pohlmann <jannis@xfce.org>
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

#ifndef __POJK_MENU_DIRECTORY_H__
#define __POJK_MENU_DIRECTORY_H__

#include <gio/gio.h>

G_BEGIN_DECLS

#define POJK_TYPE_MENU_DIRECTORY            (pojk_menu_directory_get_type ())
#define POJK_MENU_DIRECTORY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_DIRECTORY, PojkMenuDirectory))
#define POJK_MENU_DIRECTORY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_DIRECTORY, PojkMenuDirectoryClass))
#define POJK_IS_MENU_DIRECTORY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_DIRECTORY))
#define POJK_IS_MENU_DIRECTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_DIRECTORY))
#define POJK_MENU_DIRECTORY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_DIRECTORY, PojkMenuDirectoryClass))

typedef struct _PojkMenuDirectoryPrivate PojkMenuDirectoryPrivate;
typedef struct _PojkMenuDirectoryClass   PojkMenuDirectoryClass;
typedef struct _PojkMenuDirectory        PojkMenuDirectory;

struct _PojkMenuDirectoryClass
{
  GObjectClass __parent__;
};

struct _PojkMenuDirectory
{
  GObject __parent__;

  /* < private > */
  PojkMenuDirectoryPrivate *priv;
};



GType                pojk_menu_directory_get_type                (void) G_GNUC_CONST;

PojkMenuDirectory *pojk_menu_directory_new                     (GFile               *file) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

GFile               *pojk_menu_directory_get_file                (PojkMenuDirectory *directory);
const gchar         *pojk_menu_directory_get_name                (PojkMenuDirectory *directory);
void                 pojk_menu_directory_set_name                (PojkMenuDirectory *directory,
                                                                    const gchar         *name);
const gchar         *pojk_menu_directory_get_comment             (PojkMenuDirectory *directory);
void                 pojk_menu_directory_set_comment             (PojkMenuDirectory *directory,
                                                                    const gchar         *comment);
const gchar         *pojk_menu_directory_get_icon_name           (PojkMenuDirectory *directory);
void                 pojk_menu_directory_set_icon_name           (PojkMenuDirectory *directory,
                                                                    const gchar         *icon);
gboolean             pojk_menu_directory_get_no_display          (PojkMenuDirectory *directory);
void                 pojk_menu_directory_set_no_display          (PojkMenuDirectory *directory,
                                                                    gboolean             no_display);
gboolean             pojk_menu_directory_get_hidden              (PojkMenuDirectory *directory);
gboolean             pojk_menu_directory_get_show_in_environment (PojkMenuDirectory *directory);
gboolean             pojk_menu_directory_get_visible             (PojkMenuDirectory *directory);
gboolean             pojk_menu_directory_equal                   (PojkMenuDirectory *directory,
                                                                    PojkMenuDirectory *other);

G_END_DECLS

#endif /* !__POJK_MENU_DIRECTORY_H__ */
