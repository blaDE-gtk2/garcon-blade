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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_MEMORY_H
#include <memory.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <pojk/pojk-menu-item.h>
#include <pojk/pojk-menu-item-cache.h>



static void pojk_menu_item_cache_finalize   (GObject                  *object);



#if GLIB_CHECK_VERSION (2, 32, 0)
/* Object Mutex Lock */
#define _item_cache_lock(cache)    g_mutex_lock (&((cache)->priv->lock))
#define _item_cache_unlock(cache)  g_mutex_unlock (&((cache)->priv->lock))
#else
/* Mutex lock */
static GStaticMutex lock = G_STATIC_MUTEX_INIT;

#define _item_cache_lock(cache)    g_static_mutex_lock (&lock))
#define _item_cache_unlock(cache)  g_static_mutex_unlock (&lock))
#endif



struct _PojkMenuItemCachePrivate
{
  /* Hash table for mapping absolute filenames to PojkMenuItem's */
  GHashTable *items;

#if GLIB_CHECK_VERSION (2, 32, 0)
  GMutex      lock;
#endif
};



G_DEFINE_TYPE_WITH_PRIVATE (PojkMenuItemCache, pojk_menu_item_cache, G_TYPE_OBJECT)



static void
pojk_menu_item_cache_class_init (PojkMenuItemCacheClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = pojk_menu_item_cache_finalize;
}



static void
pojk_menu_item_cache_init (PojkMenuItemCache *cache)
{
  cache->priv = pojk_menu_item_cache_get_instance_private (cache);

#if GLIB_CHECK_VERSION (2, 32, 0)
  g_mutex_init (&cache->priv->lock);
#endif

  /* Create empty hash table */
  cache->priv->items = g_hash_table_new_full (g_str_hash, g_str_equal,
                                              g_free,
                                              (GDestroyNotify) pojk_menu_item_unref);
}



/**
 * pojk_menu_item_cache_get_default:
 *
 * Returns the default #PojkMenuItemCache.
 *
 * Return value: the default #PojkMenuItemCache. The returned object
 * should be unreffed with g_object_unref() when no longer needed.
 */
PojkMenuItemCache*
pojk_menu_item_cache_get_default (void)
{
  static PojkMenuItemCache *cache = NULL;

  if (G_UNLIKELY (cache == NULL))
    {
      /* Create a new cache */
      cache = g_object_new (POJK_TYPE_MENU_ITEM_CACHE, NULL);
      g_object_add_weak_pointer (G_OBJECT (cache), (gpointer) &cache);
    }
  else
    {
      /* Take a reference */
      g_object_ref (G_OBJECT (cache));
    }

  return cache;
}



static void
pojk_menu_item_cache_finalize (GObject *object)
{
  PojkMenuItemCache *cache = POJK_MENU_ITEM_CACHE (object);

  /* Free hash table */
  g_hash_table_unref (cache->priv->items);

#if GLIB_CHECK_VERSION (2, 32, 0)
  /*Release the mutex */
  g_mutex_clear (&cache->priv->lock);
#endif

  (*G_OBJECT_CLASS (pojk_menu_item_cache_parent_class)->finalize) (object);
}



PojkMenuItem*
pojk_menu_item_cache_lookup (PojkMenuItemCache *cache,
                               const gchar         *uri,
                               const gchar         *desktop_id)
{
  PojkMenuItem *item = NULL;

  g_return_val_if_fail (POJK_IS_MENU_ITEM_CACHE (cache), NULL);
  g_return_val_if_fail (uri != NULL, NULL);
  g_return_val_if_fail (desktop_id != NULL, NULL);

  /* Acquire lock on the item cache as it's likely that we need to load
   * items from the hard drive and store it in the hash table of the
   * item cache */
  _item_cache_lock (cache);

  /* Search uri in the hash table */
  item = g_hash_table_lookup (cache->priv->items, uri);

  /* Return the item if we we found one */
  if (item != NULL)
    {
      /* Update desktop id, if necessary */
      pojk_menu_item_set_desktop_id (item, desktop_id);

      /* Release item cache lock */
      _item_cache_unlock (cache);

      return item;
    }

  /* Last chance is to load it directly from the file */
  item = pojk_menu_item_new_for_uri (uri);

  if (G_LIKELY (item != NULL))
    {
      /* Update desktop id */
      pojk_menu_item_set_desktop_id (item, desktop_id);

      /* The file has been loaded, add the item to the hash table */
      g_hash_table_replace (cache->priv->items, g_strdup (uri), item);
    }

  /* Release item cache lock */
  _item_cache_unlock (cache);

  return item;
}



void
pojk_menu_item_cache_foreach (PojkMenuItemCache *cache,
                                GHFunc               func,
                                gpointer             user_data)
{
  g_return_if_fail (POJK_IS_MENU_ITEM_CACHE (cache));

  /* Acquire lock on the item cache */
  _item_cache_lock (cache);

  g_hash_table_foreach (cache->priv->items, func, user_data);

  /* Release item cache lock */
  _item_cache_unlock (cache);
}



void
pojk_menu_item_cache_invalidate (PojkMenuItemCache *cache)
{
  g_return_if_fail (POJK_IS_MENU_ITEM_CACHE (cache));

  /* Acquire lock on the item cache */
  _item_cache_lock (cache);

  /* Remove all items from the hash table */
  g_hash_table_remove_all (cache->priv->items);

  /* Release item cache lock */
  _item_cache_unlock (cache);
}



void
pojk_menu_item_cache_invalidate_file (PojkMenuItemCache *cache,
                                        GFile               *file)
{
  gchar *uri;

  g_return_if_fail (POJK_IS_MENU_ITEM_CACHE (cache));
  g_return_if_fail (G_IS_FILE (file));

  uri = g_file_get_uri (file);

  /* Acquire a lock on the item cache */
  _item_cache_lock (cache);

  /* Remove possible items with this URI from the cache */
  g_hash_table_remove (cache->priv->items, uri);

  /* Release the item cache lock */
  _item_cache_unlock (cache);

  g_free (uri);
}
