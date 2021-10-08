/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2007-2010 Jannis Pohlmann <jannis@xfce.org>
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

#ifndef __POJK_MENU_SEPARATOR_H__
#define __POJK_MENU_SEPARATOR_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define POJK_TYPE_MENU_SEPARATOR            (pojk_menu_separator_get_type())
#define POJK_MENU_SEPARATOR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_SEPARATOR, PojkMenuSeparator))
#define POJK_MENU_SEPARATOR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_SEPARATOR, PojkMenuSeparatorClass))
#define POJK_IS_MENU_SEPARATOR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_SEPARATOR))
#define POJK_IS_MENU_SEPARATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_SEPARATOR))
#define POJK_MENU_SEPARATOR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_SEPARATOR, PojkMenuSeparatorClass))

typedef struct _PojkMenuSeparatorClass PojkMenuSeparatorClass;
typedef struct _PojkMenuSeparator      PojkMenuSeparator;

struct _PojkMenuSeparatorClass
{
  GObjectClass __parent__;
};

struct _PojkMenuSeparator
{
  GObject __parent__;
};



GType                pojk_menu_separator_get_type    (void) G_GNUC_CONST;

PojkMenuSeparator *pojk_menu_separator_get_default (void);

G_END_DECLS

#endif /* !__POJK_MENU_SEPARATOR_H__ */
