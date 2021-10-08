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

#include <pojk/pojk-menu-element.h>



/**
 * SECTION: pojk-menu-element
 * @title: PojkMenuElement
 * @short_description: Central interface.
 * @include: pojk/pojk.h
 *
 * Interface implemented by the Pojk types #PojkMenuItem, #PojkMenuSeparator
 * and #PojkMenu.
 **/



GType
pojk_menu_element_get_type (void)
{
  static volatile gsize type__volatile = 0;
  GType                 type;

  if (g_once_init_enter (&type__volatile))
    {
      type = g_type_register_static_simple (G_TYPE_INTERFACE,
                                            g_intern_static_string ("PojkMenuElement"),
                                            sizeof (PojkMenuElementIface),
                                            NULL,
                                            0,
                                            NULL,
                                            0);

      g_type_interface_add_prerequisite (type, G_TYPE_OBJECT);

      g_once_init_leave (&type__volatile, type);
    }

  return type__volatile;
}



const gchar*
pojk_menu_element_get_name (PojkMenuElement *element)
{
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (element), NULL);
  return (*POJK_MENU_ELEMENT_GET_IFACE (element)->get_name) (element);
}



const gchar*
pojk_menu_element_get_comment (PojkMenuElement *element)
{
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (element), NULL);
  return (*POJK_MENU_ELEMENT_GET_IFACE (element)->get_comment) (element);
}



const gchar*
pojk_menu_element_get_icon_name (PojkMenuElement *element)
{
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (element), NULL);
  return (*POJK_MENU_ELEMENT_GET_IFACE (element)->get_icon_name) (element);
}



gboolean
pojk_menu_element_get_visible (PojkMenuElement *element)
{
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (element), FALSE);
  return (*POJK_MENU_ELEMENT_GET_IFACE (element)->get_visible) (element);
}



gboolean
pojk_menu_element_get_show_in_environment (PojkMenuElement *element)
{
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (element), FALSE);
  return (*POJK_MENU_ELEMENT_GET_IFACE (element)->get_show_in_environment) (element);
}



gboolean
pojk_menu_element_get_no_display (PojkMenuElement *element)
{
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (element), FALSE);
  return (*POJK_MENU_ELEMENT_GET_IFACE (element)->get_no_display) (element);
}



gboolean
pojk_menu_element_equal (PojkMenuElement *a,
                           PojkMenuElement *b)
{
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (a), FALSE);
  g_return_val_if_fail (POJK_IS_MENU_ELEMENT (b), FALSE);

  if (G_TYPE_FROM_INSTANCE (a) != G_TYPE_FROM_INSTANCE (b))
    return FALSE;

  return (*POJK_MENU_ELEMENT_GET_IFACE (a)->equal) (a, b);
}

