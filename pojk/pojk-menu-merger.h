/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2009-2010 Jannis Pohlmann <jannis@xfce.org>
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

#ifndef __POJK_MENU_MERGER_H__
#define __POJK_MENU_MERGER_H__

#include <pojk/pojk.h>
#include <pojk/pojk-menu-tree-provider.h>

G_BEGIN_DECLS

#define POJK_TYPE_MENU_MERGER            (pojk_menu_merger_get_type ())
#define POJK_MENU_MERGER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_MERGER, PojkMenuMerger))
#define POJK_MENU_MERGER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_MERGER, PojkMenuMergerClass))
#define POJK_IS_MENU_MERGER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_MERGER))
#define POJK_IS_MENU_MERGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_MERGER)
#define POJK_MENU_MERGER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_MERGER, PojkMenuMergerClass))

typedef struct _PojkMenuMergerPrivate PojkMenuMergerPrivate;
typedef struct _PojkMenuMergerClass   PojkMenuMergerClass;
typedef struct _PojkMenuMerger        PojkMenuMerger;

GType             pojk_menu_merger_get_type (void) G_GNUC_CONST;

PojkMenuMerger *pojk_menu_merger_new      (PojkMenuTreeProvider *provider) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
gboolean          pojk_menu_merger_run      (PojkMenuMerger       *merger,
                                               GList                 **merge_files,
                                               GList                 **merge_dirs,
                                               GCancellable           *cancellable,
                                               GError                **error);



struct _PojkMenuMergerClass
{
  GObjectClass __parent__;
};

struct _PojkMenuMerger
{
  GObject                  __parent__;

  PojkMenuMergerPrivate *priv;
};

G_END_DECLS

#endif /* !__POJK_MENU_MERGER_H__ */
