/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2006-2009 Jannis Pohlmann <jannis@xfce.org>
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

#ifndef __POJK_MENU_H__
#define __POJK_MENU_H__

#include <gio/gio.h>
#include <pojk/pojk-menu-item-pool.h>

G_BEGIN_DECLS

#define POJK_TYPE_MENU            (pojk_menu_get_type ())
#define POJK_MENU(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU, PojkMenu))
#define POJK_MENU_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU, PojkMenuClass))
#define POJK_IS_MENU(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU))
#define POJK_IS_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU))
#define POJK_MENU_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU, PojkMenuClass))

typedef struct _PojkMenuPrivate PojkMenuPrivate;
typedef struct _PojkMenuClass   PojkMenuClass;
typedef struct _PojkMenu        PojkMenu;

GType                pojk_menu_get_type           (void) G_GNUC_CONST;

PojkMenu          *pojk_menu_new                (GFile        *file) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
PojkMenu          *pojk_menu_new_for_path       (const gchar  *filename) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
PojkMenu          *pojk_menu_new_applications   (void) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
gboolean             pojk_menu_load               (PojkMenu   *menu,
                                                     GCancellable *cancellable,
                                                     GError      **error);
GFile               *pojk_menu_get_file           (PojkMenu   *menu);
PojkMenuDirectory *pojk_menu_get_directory      (PojkMenu   *menu);
GList               *pojk_menu_get_menus          (PojkMenu   *menu);
void                 pojk_menu_add_menu           (PojkMenu   *menu,
                                                     PojkMenu   *submenu);
PojkMenu          *pojk_menu_get_menu_with_name (PojkMenu   *menu,
                                                     const gchar  *name);
PojkMenu          *pojk_menu_get_parent         (PojkMenu   *menu);
PojkMenuItemPool  *pojk_menu_get_item_pool      (PojkMenu   *menu);
GList               *pojk_menu_get_items          (PojkMenu   *menu);
GList               *pojk_menu_get_elements       (PojkMenu   *menu);

struct _PojkMenuClass
{
  GObjectClass __parent__;
};

struct _PojkMenu
{
  GObject              __parent__;

  /* < private > */
  PojkMenuPrivate *priv;
};

G_END_DECLS

#endif /* !__POJK_MENU_H__ */
