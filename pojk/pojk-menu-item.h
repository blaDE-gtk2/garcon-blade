/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2006-2010 Jannis Pohlmann <jannis@xfce.org>
 * Copyright (c) 2009      Nick Schermer <nick@xfce.org>
 * Copyright (c) 2015      Danila Poyarkov <dannotemail@gmail.com>
 * Copyright (c) 2017      Gregor Santner <gsantner@mailbox.org>
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

#ifndef __POJK_MENU_ITEM_H__
#define __POJK_MENU_ITEM_H__

#include <glib-object.h>
#include <gio/gio.h>
#include <pojk/pojk-menu-item-action.h>

G_BEGIN_DECLS

typedef struct _PojkMenuItemPrivate PojkMenuItemPrivate;
typedef struct _PojkMenuItemClass   PojkMenuItemClass;
typedef struct _PojkMenuItem        PojkMenuItem;

#define POJK_TYPE_MENU_ITEM            (pojk_menu_item_get_type())
#define POJK_MENU_ITEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_ITEM, PojkMenuItem))
#define POJK_MENU_ITEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_ITEM, PojkMenuItemClass))
#define POJK_IS_MENU_ITEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_ITEM))
#define POJK_IS_MENU_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_ITEM))
#define POJK_MENU_ITEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_ITEM, PojkMenuItemClass))

#define  G_KEY_FILE_DESKTOP_KEY_KEYWORDS "Keywords"

struct _PojkMenuItemClass
{
  GObjectClass __parent__;

  /* signals */
  void (*changed) (PojkMenuItem *item);
};

struct _PojkMenuItem
{
  GObject                  __parent__;

  /* < private > */
  PojkMenuItemPrivate *priv;
};



GType                 pojk_menu_item_get_type                          (void) G_GNUC_CONST;

PojkMenuItem       *pojk_menu_item_new                               (GFile           *file) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
PojkMenuItem       *pojk_menu_item_new_for_path                      (const gchar     *filename) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
PojkMenuItem       *pojk_menu_item_new_for_uri                       (const gchar     *uri) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

gboolean              pojk_menu_item_reload                            (PojkMenuItem  *item,
                                                                    gboolean        *affects_the_outside,
                                                                    GError         **error);

gboolean              pojk_menu_item_reload_from_file                  (PojkMenuItem  *item,
                                                                    GFile           *file,
                                                                    gboolean        *affects_the_outside,
                                                                    GError         **error);

GFile                *pojk_menu_item_get_file                          (PojkMenuItem  *item);

gchar                *pojk_menu_item_get_uri                           (PojkMenuItem  *item) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

const gchar          *pojk_menu_item_get_desktop_id                    (PojkMenuItem  *item);
void                  pojk_menu_item_set_desktop_id                    (PojkMenuItem  *item,
                                                                          const gchar     *desktop_id);

const gchar          *pojk_menu_item_get_command                       (PojkMenuItem  *item);
void                  pojk_menu_item_set_command                       (PojkMenuItem  *item,
                                                                          const gchar     *command);
const gchar          *pojk_menu_item_get_try_exec                      (PojkMenuItem  *item);
void                  pojk_menu_item_set_try_exec                      (PojkMenuItem  *item,
                                                                          const gchar     *try_exec);
const gchar          *pojk_menu_item_get_name                          (PojkMenuItem  *item);
void                  pojk_menu_item_set_name                          (PojkMenuItem  *item,
                                                                          const gchar     *name);
const gchar          *pojk_menu_item_get_generic_name                  (PojkMenuItem  *item);
void                  pojk_menu_item_set_generic_name                  (PojkMenuItem  *item,
                                                                          const gchar     *generic_name);
const gchar          *pojk_menu_item_get_comment                       (PojkMenuItem  *item);
void                  pojk_menu_item_set_comment                       (PojkMenuItem  *item,
                                                                          const gchar     *comment);
const gchar          *pojk_menu_item_get_icon_name                     (PojkMenuItem  *item);
void                  pojk_menu_item_set_icon_name                     (PojkMenuItem  *item,
                                                                          const gchar     *icon_name);
const gchar          *pojk_menu_item_get_path                          (PojkMenuItem  *item);
void                  pojk_menu_item_set_path                          (PojkMenuItem  *item,
                                                                          const gchar     *path);
gboolean              pojk_menu_item_get_hidden                        (PojkMenuItem  *item);
void                  pojk_menu_item_set_hidden                        (PojkMenuItem  *item,
                                                                          gboolean         hidden);
gboolean              pojk_menu_item_requires_terminal                 (PojkMenuItem  *item);
void                  pojk_menu_item_set_requires_terminal             (PojkMenuItem  *item,
                                                                          gboolean         requires_terminal);
gboolean              pojk_menu_item_get_no_display                    (PojkMenuItem  *item);
void                  pojk_menu_item_set_no_display                    (PojkMenuItem  *item,
                                                                          gboolean         no_display);
gboolean              pojk_menu_item_supports_startup_notification     (PojkMenuItem  *item);
void                  pojk_menu_item_set_supports_startup_notification (PojkMenuItem  *item,
                                                                          gboolean         supports_startup_notification);
GList                *pojk_menu_item_get_categories                    (PojkMenuItem  *item);
void                  pojk_menu_item_set_categories                    (PojkMenuItem  *item,
                                                                          GList           *categories);
gboolean              pojk_menu_item_has_category                      (PojkMenuItem  *item,
                                                                          const gchar     *category);
GList                *pojk_menu_item_get_keywords                      (PojkMenuItem  *item);
void                  pojk_menu_item_set_keywords                      (PojkMenuItem  *item,
                                                                          GList           *keywords);
gboolean              pojk_menu_item_has_keyword                       (PojkMenuItem  *item,
                                                                          const gchar     *keyword);
GList                *pojk_menu_item_get_actions                       (PojkMenuItem  *item);
PojkMenuItemAction *pojk_menu_item_get_action                        (PojkMenuItem  *item,
                                                                          const gchar     *action_name);
void                  pojk_menu_item_set_action                        (PojkMenuItem       *item,
                                                                          const gchar          *action_name,
                                                                          PojkMenuItemAction *action);
gboolean              pojk_menu_item_has_action                        (PojkMenuItem  *item,
                                                                          const gchar     *action_name);
gboolean              pojk_menu_item_get_show_in_environment           (PojkMenuItem  *item);
gboolean              pojk_menu_item_only_show_in_environment          (PojkMenuItem  *item);
void                  pojk_menu_item_ref                               (PojkMenuItem  *item);
void                  pojk_menu_item_unref                             (PojkMenuItem  *item);
gint                  pojk_menu_item_get_allocated                     (PojkMenuItem  *item);
void                  pojk_menu_item_increment_allocated               (PojkMenuItem  *item);
void                  pojk_menu_item_decrement_allocated               (PojkMenuItem  *item);

G_END_DECLS

#endif /* !__POJK_MENU_ITEM_H__ */
