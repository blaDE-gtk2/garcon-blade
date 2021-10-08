/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2009 Jannis Pohlmann <jannis@xfce.org>
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

#if !defined (POJK_INSIDE_POJK_H) && !defined (POJK_COMPILATION)
#error "Only <pojk/pojk.h> can be included directly. This file may disappear or change contents."
#endif

#ifndef __POJK_MENU_TREE_PROVIDER_H__
#define __POJK_MENU_TREE_PROVIDER_H__

#include <gio/gio.h>

G_BEGIN_DECLS

#define POJK_TYPE_MENU_TREE_PROVIDER            (pojk_menu_tree_provider_get_type ())
#define POJK_MENU_TREE_PROVIDER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_TREE_PROVIDER, PojkMenuTreeProvider))
#define POJK_IS_MENU_TREE_PROVIDER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_TREE_PROVIDER))
#define POJK_MENU_TREE_PROVIDER_GET_IFACE(obj)  (G_TYPE_INSTANCE_GET_INTERFACE ((obj), POJK_TYPE_MENU_TREE_PROVIDER, PojkMenuTreeProviderIface))

typedef struct _PojkMenuTreeProviderIface PojkMenuTreeProviderIface;
typedef struct _PojkMenuTreeProvider      PojkMenuTreeProvider;

GType  pojk_menu_tree_provider_get_type (void) G_GNUC_CONST;

GNode *pojk_menu_tree_provider_get_tree (PojkMenuTreeProvider *provider) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
GFile *pojk_menu_tree_provider_get_file (PojkMenuTreeProvider *provider) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

struct _PojkMenuTreeProviderIface
{
  GTypeInterface __parent__;

  /* Virtual methods */
  GNode       *(*get_tree) (PojkMenuTreeProvider *provider);
  GFile       *(*get_file) (PojkMenuTreeProvider *provider);
};

G_END_DECLS

#endif /* !__POJK_MENU_TREE_PROVIDER_H__ */
