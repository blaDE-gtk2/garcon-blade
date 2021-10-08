/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2015 Danila Poyarkov <dannotemail@gmail.com>
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

#ifndef __POJK_MENU_ITEM_ACTION_H__
#define __POJK_MENU_ITEM_ACTION_H__

#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS

typedef struct _PojkMenuItemActionPrivate PojkMenuItemActionPrivate;
typedef struct _PojkMenuItemActionClass   PojkMenuItemActionClass;
typedef struct _PojkMenuItemAction        PojkMenuItemAction;

#define POJK_TYPE_MENU_ITEM_ACTION            (pojk_menu_item_action_get_type())
#define POJK_MENU_ITEM_ACTION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_ITEM_ACTION, PojkMenuItemAction))
#define POJK_MENU_ITEM_ACTION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_ITEM_ACTION, PojkMenuItemActionClass))
#define POJK_IS_MENU_ITEM_ACTION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_ITEM_ACTION))
#define POJK_IS_MENU_ITEM_ACTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_ITEM_ACTION))
#define POJK_MENU_ITEM_ACTION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_ITEM_ACTION, PojkMenuItemActionClass))

struct _PojkMenuItemActionClass
{
  GObjectClass __parent__;

  /* signals */
  void (*changed) (PojkMenuItemAction *action);
};

struct _PojkMenuItemAction
{
  GObject                  __parent__;

  /* < private > */
  PojkMenuItemActionPrivate *priv;
};

GType                 pojk_menu_item_action_get_type           (void) G_GNUC_CONST;
PojkMenuItemAction *pojk_menu_item_action_new                (void) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

const gchar          *pojk_menu_item_action_get_command        (PojkMenuItemAction  *action);
void                  pojk_menu_item_action_set_command        (PojkMenuItemAction  *action,
                                                                  const gchar           *command);
const gchar          *pojk_menu_item_action_get_name           (PojkMenuItemAction  *action);
void                  pojk_menu_item_action_set_name           (PojkMenuItemAction  *action,
                                                                  const gchar           *name);
const gchar          *pojk_menu_item_action_get_icon_name      (PojkMenuItemAction  *action);
void                  pojk_menu_item_action_set_icon_name      (PojkMenuItemAction  *action,
                                                                  const gchar           *icon_name);
void                  pojk_menu_item_action_ref                (PojkMenuItemAction  *action);
void                  pojk_menu_item_action_unref              (PojkMenuItemAction  *action);

G_END_DECLS

#endif /* !__POJK_MENU_ITEM_ACTION_H__ */
