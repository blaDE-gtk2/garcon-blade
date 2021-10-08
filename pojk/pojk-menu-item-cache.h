/* $Id$ */
/* vi:set expandtab sw=2 sts=2: */
/*-
 * Copyright (c) 2006-2007 Jannis Pohlmann <jannis@xfce.org>
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

#ifndef __POJK_MENU_ITEM_CACHE_H__
#define __POJK_MENU_ITEM_CACHE_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _PojkMenuItemCachePrivate PojkMenuItemCachePrivate;
typedef struct _PojkMenuItemCacheClass   PojkMenuItemCacheClass;
typedef struct _PojkMenuItemCache        PojkMenuItemCache;

#define POJK_TYPE_MENU_ITEM_CACHE            (pojk_menu_item_cache_get_type ())
#define POJK_MENU_ITEM_CACHE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_ITEM_CACHE, PojkMenuItemCache))
#define POJK_MENU_ITEM_CACHE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_ITEM_CACHE, PojkMenuItemCacheClass))
#define POJK_IS_MENU_ITEM_CACHE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_ITEM_CACHE))
#define POJK_IS_MENU_ITEM_CACHE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_ITEM_CACHE))
#define POJK_MENU_ITEM_CACHE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_ITEM_CACHE, PojkMenuItemCacheClass))

struct _PojkMenuItemCacheClass
{
  GObjectClass __parent__;
};

struct _PojkMenuItemCache
{
  GObject                     __parent__;

  /* Private data */
  PojkMenuItemCachePrivate *priv;
};



GType                pojk_menu_item_cache_get_type        (void) G_GNUC_CONST;

PojkMenuItemCache *pojk_menu_item_cache_get_default     (void);

PojkMenuItem      *pojk_menu_item_cache_lookup          (PojkMenuItemCache *cache,
                                                             const gchar         *uri,
                                                             const gchar         *desktop_id);
void                 pojk_menu_item_cache_foreach         (PojkMenuItemCache *cache,
                                                             GHFunc               func,
                                                             gpointer             user_data);
void                 pojk_menu_item_cache_invalidate      (PojkMenuItemCache *cache);
void                 pojk_menu_item_cache_invalidate_file (PojkMenuItemCache *cache,
                                                             GFile               *file);

G_END_DECLS

#endif /* !__POJK_MENU_ITEM_CACHE_H__ */
