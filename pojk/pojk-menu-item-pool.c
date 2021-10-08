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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <pojk/pojk-menu-node.h>
#include <pojk/pojk-menu-item-pool.h>



static void     pojk_menu_item_pool_finalize       (GObject                 *object);
static gboolean pojk_menu_item_pool_filter_exclude (const gchar             *desktop_id,
                                                      PojkMenuItem          *item,
                                                      GNode                   *node);



struct _PojkMenuItemPoolClass
{
  GObjectClass __parent__;
};

struct _PojkMenuItemPoolPrivate
{
  /* Hash table for mapping desktop-file id's to PojkMenuItem's */
  GHashTable *items;
};

struct _PojkMenuItemPool
{
  GObject                    __parent__;

  /* < private > */
  PojkMenuItemPoolPrivate *priv;
};



G_DEFINE_TYPE_WITH_PRIVATE (PojkMenuItemPool, pojk_menu_item_pool, G_TYPE_OBJECT)



static void
pojk_menu_item_pool_class_init (PojkMenuItemPoolClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = pojk_menu_item_pool_finalize;
}



static void
pojk_menu_item_pool_init (PojkMenuItemPool *pool)
{
  pool->priv = pojk_menu_item_pool_get_instance_private (pool);
  pool->priv->items = g_hash_table_new_full (g_str_hash, g_str_equal,
                                             g_free,
                                             (GDestroyNotify) pojk_menu_item_unref);
}



static void
pojk_menu_item_pool_finalize (GObject *object)
{
  PojkMenuItemPool *pool = POJK_MENU_ITEM_POOL (object);

  g_hash_table_unref (pool->priv->items);

  (*G_OBJECT_CLASS (pojk_menu_item_pool_parent_class)->finalize) (object);
}



PojkMenuItemPool*
pojk_menu_item_pool_new (void)
{
  return g_object_new (POJK_TYPE_MENU_ITEM_POOL, NULL);
}



void
pojk_menu_item_pool_insert (PojkMenuItemPool *pool,
                              PojkMenuItem     *item)
{
  g_return_if_fail (POJK_IS_MENU_ITEM_POOL (pool));
  g_return_if_fail (POJK_IS_MENU_ITEM (item));

  /* Insert into the hash table and remove old item (if any) */
  g_hash_table_replace (pool->priv->items, g_strdup (pojk_menu_item_get_desktop_id (item)), item);

  /* Grab a reference on the item */
  pojk_menu_item_ref (item);
}



PojkMenuItem*
pojk_menu_item_pool_lookup (PojkMenuItemPool *pool,
                              const gchar        *desktop_id)
{
  g_return_val_if_fail (POJK_IS_MENU_ITEM_POOL (pool), NULL);
  g_return_val_if_fail (desktop_id != NULL, NULL);

  return g_hash_table_lookup (pool->priv->items, desktop_id);
}



PojkMenuItem *
pojk_menu_item_pool_lookup_file (PojkMenuItemPool *pool,
                                   GFile              *file)
{
  PojkMenuItem *result = NULL;
  GHashTableIter  iter;
  gpointer        item;
  GFile          *item_file;

  g_return_val_if_fail (POJK_IS_MENU_ITEM_POOL (pool), NULL);
  g_return_val_if_fail (G_IS_FILE (file), NULL);

  g_hash_table_iter_init (&iter, pool->priv->items);
  while (result == NULL && g_hash_table_iter_next (&iter, NULL, &item))
    {
      item_file = pojk_menu_item_get_file (item);

      if (g_file_equal (item_file, file))
        result = item;

      g_object_unref (item_file);
    }

  return result;
}



void
pojk_menu_item_pool_foreach (PojkMenuItemPool *pool,
                               GHFunc              func,
                               gpointer            user_data)
{
  g_return_if_fail (POJK_IS_MENU_ITEM_POOL (pool));

  g_hash_table_foreach (pool->priv->items, func, user_data);
}



void
pojk_menu_item_pool_apply_exclude_rule (PojkMenuItemPool *pool,
                                          GNode              *node)
{
  g_return_if_fail (POJK_IS_MENU_ITEM_POOL (pool));
  g_return_if_fail (node != NULL);

  /* Remove all items which match this exclude rule */
  g_hash_table_foreach_remove (pool->priv->items, (GHRFunc) pojk_menu_item_pool_filter_exclude, node);
}



static gboolean
pojk_menu_item_pool_filter_exclude (const gchar    *desktop_id,
                                      PojkMenuItem *item,
                                      GNode          *node)
{
  gboolean matches;

  g_return_val_if_fail (POJK_IS_MENU_ITEM (item), FALSE);
  g_return_val_if_fail (node != NULL, FALSE);

  matches = pojk_menu_node_tree_rule_matches (node, item);

  if (matches)
    pojk_menu_item_increment_allocated (item);

  return matches;
}



gboolean
pojk_menu_item_pool_get_empty (PojkMenuItemPool *pool)
{
  g_return_val_if_fail (POJK_IS_MENU_ITEM_POOL (pool), TRUE);
  return (g_hash_table_size (pool->priv->items) == 0);
}



void
pojk_menu_item_pool_clear (PojkMenuItemPool *pool)
{
  g_return_if_fail (POJK_IS_MENU_ITEM_POOL (pool));
  g_hash_table_remove_all (pool->priv->items);
}
