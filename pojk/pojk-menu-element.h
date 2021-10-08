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

#if !defined (POJK_INSIDE_POJK_H) && !defined (POJK_COMPILATION)
#error "Only <pojk/pojk.h> can be included directly. This file may disappear or change contents."
#endif

#ifndef __POJK_MENU_ELEMENT_H__
#define __POJK_MENU_ELEMENT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define POJK_TYPE_MENU_ELEMENT           (pojk_menu_element_get_type ())
#define POJK_MENU_ELEMENT(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_ELEMENT, PojkMenuElement))
#define POJK_IS_MENU_ELEMENT(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_ELEMENT))
#define POJK_MENU_ELEMENT_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), POJK_TYPE_MENU_ELEMENT, PojkMenuElementIface))

typedef struct _PojkMenuElement      PojkMenuElement;
typedef struct _PojkMenuElementIface PojkMenuElementIface;

struct _PojkMenuElementIface
{
  GTypeInterface __parent__;

  /* Virtual methods */
  const gchar *(*get_name)                (PojkMenuElement *element);
  const gchar *(*get_comment)             (PojkMenuElement *element);
  const gchar *(*get_icon_name)           (PojkMenuElement *element);
  gboolean     (*get_visible)             (PojkMenuElement *element);
  gboolean     (*get_show_in_environment) (PojkMenuElement *element);
  gboolean     (*get_no_display)          (PojkMenuElement *element);
  gboolean     (*equal)                   (PojkMenuElement *element,
                                           PojkMenuElement *other);
};

GType        pojk_menu_element_get_type                (void) G_GNUC_CONST;

const gchar *pojk_menu_element_get_name                (PojkMenuElement *element);
const gchar *pojk_menu_element_get_comment             (PojkMenuElement *element);
const gchar *pojk_menu_element_get_icon_name           (PojkMenuElement *element);
gboolean     pojk_menu_element_get_visible             (PojkMenuElement *element);
gboolean     pojk_menu_element_get_show_in_environment (PojkMenuElement *element);
gboolean     pojk_menu_element_get_no_display          (PojkMenuElement *element);
gboolean     pojk_menu_element_equal                   (PojkMenuElement *a,
                                                          PojkMenuElement *b);

G_END_DECLS

#endif /* !__POJK_MENU_ELEMENT_H__ */
