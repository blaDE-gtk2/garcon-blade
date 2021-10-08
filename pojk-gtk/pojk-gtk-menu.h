/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2013 Nick Schermer <nick@xfce.org>
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

#if !defined(POJK_INSIDE_POJK_GTK_H) && !defined(POJK_COMPILATION)
#error "Only <pojk-gtk/pojk-gtk.h> can be included directly. This file may disappear or change contents."
#endif

#ifndef __POJK_GTK_MENU_H__
#define __POJK_GTK_MENU_H__

#include <gtk/gtk.h>
#include <pojk/pojk.h>

G_BEGIN_DECLS

#define POJK_GTK_TYPE_MENU            (pojk_gtk_menu_get_type ())
#define POJK_GTK_MENU(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_GTK_TYPE_MENU, PojkGtkMenu))
#define POJK_GTK_MENU_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_GTK_TYPE_MENU, PojktkMenuClass))
#define POJK_GTK_IS_MENU(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_GTK_TYPE_MENU))
#define POJK_GTK_IS_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_GTK_TYPE_MENU))
#define POJK_GTK_MENU_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_GTK_TYPE_MENU, PojktkMenuClass))

typedef struct _PojkGtkMenuPrivate PojkGtkMenuPrivate;
typedef struct _PojkGtkMenuClass   PojkGtkMenuClass;
typedef struct _PojkGtkMenu        PojkGtkMenu;

struct _PojkGtkMenuClass
{
  GtkMenuClass __parent__;
};

struct _PojkGtkMenu
{
  GtkMenu              __parent__;

  /* < private > */
  PojkGtkMenuPrivate *priv;
};

GType                pojk_gtk_menu_get_type                 (void) G_GNUC_CONST;

GtkWidget           *pojk_gtk_menu_new                      (PojkMenu    *pojk_menu) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

void                 pojk_gtk_menu_set_menu                 (PojkGtkMenu *menu,
                                                               PojkMenu    *pojk_menu);

PojkMenu          *pojk_gtk_menu_get_menu                 (PojkGtkMenu *menu);

void                 pojk_gtk_menu_set_show_generic_names   (PojkGtkMenu *menu,
                                                               gboolean       show_generic_names);
gboolean             pojk_gtk_menu_get_show_generic_names   (PojkGtkMenu *menu);

void                 pojk_gtk_menu_set_show_menu_icons      (PojkGtkMenu *menu,
                                                               gboolean       show_menu_icons);
gboolean             pojk_gtk_menu_get_show_menu_icons      (PojkGtkMenu *menu);

void                 pojk_gtk_menu_set_show_tooltips        (PojkGtkMenu *menu,
                                                               gboolean       show_tooltips);
gboolean             pojk_gtk_menu_get_show_tooltips        (PojkGtkMenu *menu);

void                 pojk_gtk_menu_set_show_desktop_actions (PojkGtkMenu *menu,
                                                               gboolean       show_desktop_actions);
gboolean             pojk_gtk_menu_get_show_desktop_actions (PojkGtkMenu *menu);

void                 pojk_gtk_menu_set_right_click_edits    (PojkGtkMenu *menu,
                                                               gboolean       enable_right_click_edits);
gboolean             pojk_gtk_menu_get_right_click_edits    (PojkGtkMenu *menu);

G_END_DECLS

#endif /* !__POJK_GTK_MENU_H__ */
