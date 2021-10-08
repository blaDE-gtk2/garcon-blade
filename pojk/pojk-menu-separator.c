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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <pojk/pojk-menu-element.h>
#include <pojk/pojk-menu-separator.h>



static void         pojk_menu_separator_element_init                    (PojkMenuElementIface   *iface);
static void         pojk_menu_separator_finalize                        (GObject                  *object);

static const gchar *pojk_menu_separator_get_element_name                (PojkMenuElement        *element);
static const gchar *pojk_menu_separator_get_element_comment             (PojkMenuElement        *element);
static const gchar *pojk_menu_separator_get_element_icon_name           (PojkMenuElement        *element);
static gboolean     pojk_menu_separator_get_element_visible             (PojkMenuElement        *element);
static gboolean     pojk_menu_separator_get_element_show_in_environment (PojkMenuElement        *element);
static gboolean     pojk_menu_separator_get_element_no_display          (PojkMenuElement        *element);
static gboolean     pojk_menu_separator_get_element_equal               (PojkMenuElement        *element,
                                                                           PojkMenuElement        *other);



G_DEFINE_TYPE_WITH_CODE (PojkMenuSeparator, pojk_menu_separator, G_TYPE_OBJECT,
    G_IMPLEMENT_INTERFACE (POJK_TYPE_MENU_ELEMENT, pojk_menu_separator_element_init))



static void
pojk_menu_separator_class_init (PojkMenuSeparatorClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = pojk_menu_separator_finalize;
}



static void
pojk_menu_separator_element_init (PojkMenuElementIface *iface)
{
  iface->get_name = pojk_menu_separator_get_element_name;
  iface->get_comment = pojk_menu_separator_get_element_comment;
  iface->get_icon_name = pojk_menu_separator_get_element_icon_name;
  iface->get_visible = pojk_menu_separator_get_element_visible;
  iface->get_show_in_environment = pojk_menu_separator_get_element_show_in_environment;
  iface->get_no_display = pojk_menu_separator_get_element_no_display;
  iface->equal = pojk_menu_separator_get_element_equal;
}



static void
pojk_menu_separator_init (PojkMenuSeparator *separator)
{
}



static void
pojk_menu_separator_finalize (GObject *object)
{
  (*G_OBJECT_CLASS (pojk_menu_separator_parent_class)->finalize) (object);
}



/**
 * pojk_menu_separator_get_default:
 *
 * Returns the default #PojkMenuSeparator.
 *
 * Return value: the default #PojkMenuSeparator. The returned object
 * should be unreffed with g_object_unref() when no longer needed.
 */
PojkMenuSeparator*
pojk_menu_separator_get_default (void)
{
  static PojkMenuSeparator *separator = NULL;

  if (G_UNLIKELY (separator == NULL))
    {
      /* Create a new separator */
      separator = g_object_new (POJK_TYPE_MENU_SEPARATOR, NULL);
      g_object_add_weak_pointer (G_OBJECT (separator), (gpointer) &separator);
    }
  else
    {
      /* Take a reference */
      g_object_ref (G_OBJECT (separator));
    }

  return separator;
}



static const gchar*
pojk_menu_separator_get_element_name (PojkMenuElement *element)
{
  return NULL;
}



static const gchar*
pojk_menu_separator_get_element_comment (PojkMenuElement *element)
{
  return NULL;
}



static const gchar*
pojk_menu_separator_get_element_icon_name (PojkMenuElement *element)
{
  return NULL;
}



static gboolean
pojk_menu_separator_get_element_visible (PojkMenuElement *element)
{
  return TRUE;
}



static gboolean
pojk_menu_separator_get_element_show_in_environment (PojkMenuElement *element)
{
  return TRUE;
}



static gboolean
pojk_menu_separator_get_element_no_display (PojkMenuElement *element)
{
  return FALSE;
}



static gboolean
pojk_menu_separator_get_element_equal (PojkMenuElement *element,
                                         PojkMenuElement *other)
{
  /* FIXME this is inherently broken as the separator is a singleton class */
  return FALSE;
}
