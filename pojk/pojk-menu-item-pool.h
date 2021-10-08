/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2006-2010 Jannis Pohlmann <jannis@xfce.org>
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

#ifndef __POJK_MENU_ITEM_POOL_H__
#define __POJK_MENU_ITEM_POOL_H__

#include <glib-object.h>
#include <pojk/pojk-menu-item.h>

G_BEGIN_DECLS

#define POJK_TYPE_MENU_ITEM_POOL            (pojk_menu_item_pool_get_type ())
#define POJK_MENU_ITEM_POOL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_ITEM_POOL, PojkMenuItemPool))
#define POJK_MENU_ITEM_POOL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_ITEM_POOL, PojkMenuItemPoolClass))
#define POJK_IS_MENU_ITEM_POOL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_ITEM_POOL))
#define POJK_IS_MENU_ITEM_POOL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_ITEM_POOL))
#define POJK_MENU_ITEM_POOL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_ITEM_POOL, PojkMenuItemPoolClass))

typedef struct _PojkMenuItemPoolPrivate PojkMenuItemPoolPrivate;
typedef struct _PojkMenuItemPoolClass   PojkMenuItemPoolClass;
typedef struct _PojkMenuItemPool        PojkMenuItemPool;

GType               pojk_menu_item_pool_get_type           (void) G_GNUC_CONST;

PojkMenuItemPool *pojk_menu_item_pool_new                (void) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

void                pojk_menu_item_pool_insert             (PojkMenuItemPool *pool,
                                                              PojkMenuItem     *item);
PojkMenuItem     *pojk_menu_item_pool_lookup             (PojkMenuItemPool *pool,
                                                              const gchar        *desktop_id);
PojkMenuItem     *pojk_menu_item_pool_lookup_file        (PojkMenuItemPool *pool,
                                                              GFile              *file);
void                pojk_menu_item_pool_foreach            (PojkMenuItemPool *pool,
                                                              GHFunc              func,
                                                              gpointer            user_data);
void                pojk_menu_item_pool_apply_exclude_rule (PojkMenuItemPool *pool,
                                                              GNode              *node);
gboolean            pojk_menu_item_pool_get_empty          (PojkMenuItemPool *pool);
void                pojk_menu_item_pool_clear              (PojkMenuItemPool *pool);

G_END_DECLS

#endif /* !__POJK_MENU_ITEM_POOL_H__ */
