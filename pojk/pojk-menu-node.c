/* vi:set sw=2 sts=2 ts=2 et ai: */
/*-
 * Copyright (c) 2009 Jannis Pohlmann <jannis@xfce.org>.
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

#include <glib.h>
#include <glib-object.h>

#include <pojk/pojk-menu-item.h>
#include <pojk/pojk-menu-node.h>



/* Property identifiers */
enum
{
  PROP_0,
  PROP_NODE_TYPE,
};



static void pojk_menu_node_finalize     (GObject             *object);
static void pojk_menu_node_get_property (GObject             *object,
                                           guint                prop_id,
                                           GValue              *value,
                                           GParamSpec          *pspec);
static void pojk_menu_node_set_property (GObject             *object,
                                           guint                prop_id,
                                           const GValue        *value,
                                           GParamSpec          *pspec);
static void pojk_menu_node_free_data    (PojkMenuNode      *node);



struct _PojkMenuNodeClass
{
  GObjectClass __parent__;
};

union _PojkMenuNodeData
{
  PojkMenuLayoutMergeType layout_merge_type;
  struct
  {
    PojkMenuMergeFileType type;
    gchar                  *filename;
  } merge_file;
  gchar                    *string;
};

struct _PojkMenuNode
{
  GObject            __parent__;

  PojkMenuNodeType node_type;
  PojkMenuNodeData data;
};



GType
pojk_menu_node_type_get_type (void)
{
  static GType      type = G_TYPE_INVALID;
  static GEnumValue values[] =
  {
    { POJK_MENU_NODE_TYPE_INVALID, "POJK_MENU_NODE_TYPE_INVALID", "Invalid" },
    { POJK_MENU_NODE_TYPE_MENU, "POJK_MENU_NODE_TYPE_MENU", "Menu" },
    { POJK_MENU_NODE_TYPE_NAME, "POJK_MENU_NODE_TYPE_NAME", "Name" },
    { POJK_MENU_NODE_TYPE_DIRECTORY, "POJK_MENU_NODE_TYPE_DIRECTORY", "Directory" },
    { POJK_MENU_NODE_TYPE_DIRECTORY_DIR, "POJK_MENU_NODE_TYPE_DIRECTORY_DIR", "DirectoryDir" },
    { POJK_MENU_NODE_TYPE_DEFAULT_DIRECTORY_DIRS, "POJK_MENU_NODE_TYPE_DEFAULT_DIRECTORY_DIRS", "DefaultDirectoryDirs" },
    { POJK_MENU_NODE_TYPE_APP_DIR, "POJK_MENU_NODE_TYPE_APP_DIR", "AppDir" },
    { POJK_MENU_NODE_TYPE_DEFAULT_APP_DIRS, "POJK_MENU_NODE_TYPE_DEFAULT_APP_DIRS", "DefaultAppDirs" },
    { POJK_MENU_NODE_TYPE_ONLY_UNALLOCATED, "POJK_MENU_NODE_TYPE_ONLY_UNALLOCATED", "OnlyUnallocated" },
    { POJK_MENU_NODE_TYPE_NOT_ONLY_UNALLOCATED, "POJK_MENU_NODE_TYPE_NOT_ONLY_UNALLOCATED", "NotOnlyUnallocated" },
    { POJK_MENU_NODE_TYPE_DELETED, "POJK_MENU_NODE_TYPE_DELETED", "Deleted" },
    { POJK_MENU_NODE_TYPE_NOT_DELETED, "POJK_MENU_NODE_TYPE_NOT_DELETED", "NotDeleted" },
    { POJK_MENU_NODE_TYPE_INCLUDE, "POJK_MENU_NODE_TYPE_INCLUDE", "Include" },
    { POJK_MENU_NODE_TYPE_EXCLUDE, "POJK_MENU_NODE_TYPE_EXCLUDE", "Exclude" },
    { POJK_MENU_NODE_TYPE_ALL, "POJK_MENU_NODE_TYPE_ALL", "All" },
    { POJK_MENU_NODE_TYPE_FILENAME, "POJK_MENU_NODE_TYPE_FILENAME", "Filename" },
    { POJK_MENU_NODE_TYPE_CATEGORY, "POJK_MENU_NODE_TYPE_CATEGORY", "Category" },
    { POJK_MENU_NODE_TYPE_OR, "POJK_MENU_NODE_TYPE_OR", "Or" },
    { POJK_MENU_NODE_TYPE_AND, "POJK_MENU_NODE_TYPE_AND", "And" },
    { POJK_MENU_NODE_TYPE_NOT, "POJK_MENU_NODE_TYPE_NOT", "Not" },
    { POJK_MENU_NODE_TYPE_MOVE, "POJK_MENU_NODE_TYPE_MOVE", "Move" },
    { POJK_MENU_NODE_TYPE_OLD, "POJK_MENU_NODE_TYPE_OLD", "Old" },
    { POJK_MENU_NODE_TYPE_NEW, "POJK_MENU_NODE_TYPE_NEW", "New" },
    { POJK_MENU_NODE_TYPE_DEFAULT_LAYOUT, "POJK_MENU_NODE_TYPE_DEFAULT_LAYOUT", "DefaultLayout" },
    { POJK_MENU_NODE_TYPE_LAYOUT, "POJK_MENU_NODE_TYPE_LAYOUT", "Layout" },
    { POJK_MENU_NODE_TYPE_MENUNAME, "POJK_MENU_NODE_TYPE_MENUNAME", "Menuname" },
    { POJK_MENU_NODE_TYPE_SEPARATOR, "POJK_MENU_NODE_TYPE_SEPARATOR", "Separator" },
    { POJK_MENU_NODE_TYPE_MERGE, "POJK_MENU_NODE_TYPE_MERGE", "Merge" },
    { POJK_MENU_NODE_TYPE_MERGE_FILE, "POJK_MENU_NODE_TYPE_MERGE_FILE", "MergeFile" },
    { POJK_MENU_NODE_TYPE_MERGE_DIR, "POJK_MENU_NODE_TYPE_MERGE_DIR", "MergeDir" },
    { POJK_MENU_NODE_TYPE_DEFAULT_MERGE_DIRS, "POJK_MENU_NODE_TYPE_DEFAULT_MERGE_DIRS", "MergeDirs" },
    { 0, NULL, NULL },
  };

  if (G_UNLIKELY (type == G_TYPE_INVALID))
    type = g_enum_register_static ("PojkMenuNodeType", values);

  return type;
}



G_DEFINE_TYPE (PojkMenuNode, pojk_menu_node, G_TYPE_OBJECT)



static void
pojk_menu_node_class_init (PojkMenuNodeClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = pojk_menu_node_finalize;
  gobject_class->get_property = pojk_menu_node_get_property;
  gobject_class->set_property = pojk_menu_node_set_property;

  g_object_class_install_property (gobject_class,
                                   PROP_NODE_TYPE,
                                   g_param_spec_enum ("node-type",
                                                      "node-type",
                                                      "node-type",
                                                      pojk_menu_node_type_get_type (),
                                                      POJK_MENU_NODE_TYPE_MENU,
                                                      G_PARAM_READWRITE |
                                                      G_PARAM_STATIC_STRINGS));
}



static void
pojk_menu_node_init (PojkMenuNode *node)
{
}



static void
pojk_menu_node_finalize (GObject *object)
{
  PojkMenuNode *node = POJK_MENU_NODE (object);

  pojk_menu_node_free_data (node);

  (*G_OBJECT_CLASS (pojk_menu_node_parent_class)->finalize) (object);
}



static void
pojk_menu_node_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  PojkMenuNode *node = POJK_MENU_NODE (object);

  switch (prop_id)
    {
    case PROP_NODE_TYPE:
      g_value_set_enum (value, node->node_type);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}



static void
pojk_menu_node_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  PojkMenuNode *node = POJK_MENU_NODE (object);

  switch (prop_id)
    {
    case PROP_NODE_TYPE:
      node->node_type = g_value_get_enum (value);
      g_object_notify (G_OBJECT (node), "node-type");
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}



PojkMenuNode *
pojk_menu_node_new (PojkMenuNodeType node_type)
{
  return g_object_new (POJK_TYPE_MENU_NODE, "node-type", node_type, NULL);
}



PojkMenuNodeType pojk_menu_node_get_node_type (PojkMenuNode *node)
{
  g_return_val_if_fail (POJK_IS_MENU_NODE (node), 0);
  return node->node_type;
}



PojkMenuNode *
pojk_menu_node_create (PojkMenuNodeType node_type,
                         gpointer           first_value,
                         ...)
{
  PojkMenuNode *node;

  node = pojk_menu_node_new (node_type);

  switch (node_type)
    {
    case POJK_MENU_NODE_TYPE_NAME:
    case POJK_MENU_NODE_TYPE_DIRECTORY:
    case POJK_MENU_NODE_TYPE_DIRECTORY_DIR:
    case POJK_MENU_NODE_TYPE_APP_DIR:
    case POJK_MENU_NODE_TYPE_FILENAME:
    case POJK_MENU_NODE_TYPE_CATEGORY:
    case POJK_MENU_NODE_TYPE_OLD:
    case POJK_MENU_NODE_TYPE_NEW:
    case POJK_MENU_NODE_TYPE_MENUNAME:
    case POJK_MENU_NODE_TYPE_MERGE_DIR:
      node->data.string = g_strdup (first_value);
      break;

    case POJK_MENU_NODE_TYPE_MERGE:
      node->data.layout_merge_type = GPOINTER_TO_UINT (first_value);
      break;

    case POJK_MENU_NODE_TYPE_MERGE_FILE:
      node->data.merge_file.type = GPOINTER_TO_UINT (first_value);
      node->data.merge_file.filename = NULL;
      break;

    default:
      break;
    }

  return node;
}



PojkMenuNode *
pojk_menu_node_copy (PojkMenuNode *node,
                       gpointer        data)
{
  PojkMenuNode *copy;

  if (node == NULL || !POJK_IS_MENU_NODE (node))
    return NULL;

  copy = pojk_menu_node_new (node->node_type);

  switch (copy->node_type)
    {
    case POJK_MENU_NODE_TYPE_NAME:
    case POJK_MENU_NODE_TYPE_DIRECTORY:
    case POJK_MENU_NODE_TYPE_DIRECTORY_DIR:
    case POJK_MENU_NODE_TYPE_APP_DIR:
    case POJK_MENU_NODE_TYPE_FILENAME:
    case POJK_MENU_NODE_TYPE_CATEGORY:
    case POJK_MENU_NODE_TYPE_OLD:
    case POJK_MENU_NODE_TYPE_NEW:
    case POJK_MENU_NODE_TYPE_MENUNAME:
    case POJK_MENU_NODE_TYPE_MERGE_DIR:
      copy->data.string = g_strdup (node->data.string);
      break;

    case POJK_MENU_NODE_TYPE_MERGE:
      copy->data.layout_merge_type = node->data.layout_merge_type;
      break;

    case POJK_MENU_NODE_TYPE_MERGE_FILE:
      copy->data.merge_file.type = node->data.merge_file.type;
      copy->data.merge_file.filename = g_strdup (node->data.merge_file.filename);
      break;

    default:
      break;
    }

  return copy;
}



static void
pojk_menu_node_free_data (PojkMenuNode *node)
{
  g_return_if_fail (POJK_IS_MENU_NODE (node));

  switch (node->node_type)
    {
    case POJK_MENU_NODE_TYPE_NAME:
    case POJK_MENU_NODE_TYPE_DIRECTORY:
    case POJK_MENU_NODE_TYPE_DIRECTORY_DIR:
    case POJK_MENU_NODE_TYPE_APP_DIR:
    case POJK_MENU_NODE_TYPE_FILENAME:
    case POJK_MENU_NODE_TYPE_CATEGORY:
    case POJK_MENU_NODE_TYPE_OLD:
    case POJK_MENU_NODE_TYPE_NEW:
    case POJK_MENU_NODE_TYPE_MENUNAME:
    case POJK_MENU_NODE_TYPE_MERGE_DIR:
      g_free (node->data.string);
      break;

    case POJK_MENU_NODE_TYPE_MERGE_FILE:
      g_free (node->data.merge_file.filename);
      break;

    default:
      break;
    }
}



const gchar *
pojk_menu_node_get_string (PojkMenuNode *node)
{
  g_return_val_if_fail (POJK_IS_MENU_NODE (node), NULL);
  return node->data.string;
}



void
pojk_menu_node_set_string (PojkMenuNode *node,
                             const gchar    *value)
{
  g_return_if_fail (POJK_IS_MENU_NODE (node));
  g_return_if_fail (value != NULL);

  g_free (node->data.string);
  node->data.string = g_strdup (value);
}



PojkMenuMergeFileType
pojk_menu_node_get_merge_file_type (PojkMenuNode *node)
{
  g_return_val_if_fail (POJK_IS_MENU_NODE (node), 0);
  g_return_val_if_fail (node->node_type == POJK_MENU_NODE_TYPE_MERGE_FILE, 0);
  return node->data.merge_file.type;
}



void
pojk_menu_node_set_merge_file_type (PojkMenuNode         *node,
                                      PojkMenuMergeFileType type)
{
  g_return_if_fail (POJK_IS_MENU_NODE (node));
  g_return_if_fail (node->node_type == POJK_MENU_NODE_TYPE_MERGE_FILE);
  node->data.merge_file.type = type;
}



const gchar *
pojk_menu_node_get_merge_file_filename (PojkMenuNode *node)
{
  g_return_val_if_fail (POJK_IS_MENU_NODE (node), NULL);
  g_return_val_if_fail (node->node_type == POJK_MENU_NODE_TYPE_MERGE_FILE, NULL);
  return node->data.merge_file.filename;
}



void
pojk_menu_node_set_merge_file_filename (PojkMenuNode *node,
                                          const gchar    *filename)
{
  g_return_if_fail (POJK_IS_MENU_NODE (node));
  g_return_if_fail (filename != NULL);
  g_return_if_fail (node->node_type == POJK_MENU_NODE_TYPE_MERGE_FILE);

  g_free (node->data.merge_file.filename);
  node->data.merge_file.filename = g_strdup (filename);
}



typedef struct
{
  PojkMenuNodeType type;
  GNode             *self;
  gpointer           value;
} Pair;



static gboolean
collect_children (GNode *node,
                  Pair  *pair)
{
  if (node == pair->self)
    return FALSE;

  if (pojk_menu_node_tree_get_node_type (node) == pair->type)
    pair->value = g_list_prepend (pair->value, node);

  return FALSE;
}



GNode *
pojk_menu_node_tree_get_child_node (GNode             *tree,
                                      PojkMenuNodeType type,
                                      gboolean           reverse)
{
  GNode *child;

  if (reverse)
    {
      for (child = g_node_last_child (tree); 
           child != NULL;
           child = g_node_prev_sibling (child))
        {
          if (pojk_menu_node_tree_get_node_type (child) == type)
            return child;
        }
    }
  else
    {
      for (child = g_node_first_child (tree);
           child != NULL;
           child = g_node_next_sibling (child))
        {
          if (pojk_menu_node_tree_get_node_type (child) == type)
            return child;
        }
    }

  return NULL;
}



GList *
pojk_menu_node_tree_get_child_nodes (GNode             *tree,
                                       PojkMenuNodeType type,
                                       gboolean           reverse)
{
  Pair pair;

  pair.type = type;
  pair.value = NULL;
  pair.self = tree;

  g_node_traverse (tree, G_IN_ORDER, G_TRAVERSE_ALL, 2,
                   (GNodeTraverseFunc) collect_children, &pair);

  /* Return the list as if we appended */
  if (!reverse && pair.value != NULL)
    pair.value = g_list_reverse (pair.value);

  return pair.value;
}



static gboolean
collect_strings (GNode *node,
                 Pair  *pair)
{
  gpointer string;

  if (node == pair->self)
    return FALSE;

  if (pojk_menu_node_tree_get_node_type (node) == pair->type)
    {
      string = (gpointer) pojk_menu_node_tree_get_string (node);
      pair->value = g_list_prepend (pair->value, string);
    }

  return FALSE;
}



GList *
pojk_menu_node_tree_get_string_children (GNode             *tree,
                                           PojkMenuNodeType type,
                                           gboolean           reverse)
{
  Pair pair;

  pair.type = type;
  pair.value = NULL;
  pair.self = tree;

  g_node_traverse (tree, G_IN_ORDER, G_TRAVERSE_ALL, 2,
                   (GNodeTraverseFunc) collect_strings, &pair);

  /* Return the list as if we appended */
  if (!reverse && pair.value != NULL)
    pair.value = g_list_reverse (pair.value);

  return pair.value;
}



static gboolean
collect_boolean (GNode *node,
                 Pair  *pair)
{
  if (node == pair->self)
    return FALSE;

  if (pojk_menu_node_tree_get_node_type (node) == pair->type)
    {
      pair->value = GUINT_TO_POINTER (1);
      return TRUE;
    }

  return FALSE;
}



gboolean
pojk_menu_node_tree_get_boolean_child (GNode             *tree,
                                         PojkMenuNodeType type)
{
  Pair pair;

  pair.value = GUINT_TO_POINTER (0);
  pair.self = tree;
  pair.type = type;

  g_node_traverse (tree, G_IN_ORDER, G_TRAVERSE_ALL, 2,
                   (GNodeTraverseFunc) collect_boolean, &pair);

  return !!GPOINTER_TO_UINT (pair.value);
}



static gboolean
collect_string (GNode *node,
                Pair  *pair)
{
  const gchar **string = pair->value;

  if (node == pair->self)
    return FALSE;

  if (pojk_menu_node_tree_get_node_type (node) == pair->type)
    {
      *string = pojk_menu_node_tree_get_string (node);
      return TRUE;
    }

  return FALSE;
}



const gchar *
pojk_menu_node_tree_get_string_child (GNode             *tree,
                                        PojkMenuNodeType type)
{
  Pair         pair;
  const gchar *string = NULL;

  pair.type = type;
  pair.value = &string;
  pair.self = tree;

  g_node_traverse (tree, G_IN_ORDER, G_TRAVERSE_ALL, 2,
                   (GNodeTraverseFunc) collect_string, &pair);

  return string;
}



gboolean
pojk_menu_node_tree_rule_matches (GNode          *node,
                                    PojkMenuItem *item)
{
  GNode   *child;
  gboolean matches = FALSE;
  gboolean child_matches = FALSE;

  switch (pojk_menu_node_tree_get_node_type (node))
    {
    case POJK_MENU_NODE_TYPE_CATEGORY:
      matches = pojk_menu_item_has_category (item, pojk_menu_node_tree_get_string (node));
      break;

    case POJK_MENU_NODE_TYPE_INCLUDE:
    case POJK_MENU_NODE_TYPE_EXCLUDE:
    case POJK_MENU_NODE_TYPE_OR:
      for (child = g_node_first_child (node); child != NULL; child = g_node_next_sibling (child))
        matches = matches || pojk_menu_node_tree_rule_matches (child, item);
      break;

    case POJK_MENU_NODE_TYPE_FILENAME:
      matches = g_str_equal (pojk_menu_node_tree_get_string (node),
                             pojk_menu_item_get_desktop_id (item));
      break;

    case POJK_MENU_NODE_TYPE_AND:
      matches = TRUE;
      for (child = g_node_first_child (node); child != NULL; child = g_node_next_sibling (child))
        matches = matches && pojk_menu_node_tree_rule_matches (child, item);
      break;

    case POJK_MENU_NODE_TYPE_NOT:
      for (child = g_node_first_child (node); child != NULL; child = g_node_next_sibling (child))
        child_matches = child_matches || pojk_menu_node_tree_rule_matches (child, item);
      matches = !child_matches;
      break;

    case POJK_MENU_NODE_TYPE_ALL:
      matches = TRUE;
      break;

    default:
      break;
    }

  return matches;
}






PojkMenuNodeType
pojk_menu_node_tree_get_node_type (GNode *tree)
{
  if (tree == NULL)
    return POJK_MENU_NODE_TYPE_INVALID;

  if (tree->data == NULL)
    return POJK_MENU_NODE_TYPE_MENU;

  return pojk_menu_node_get_node_type (tree->data);
}



const gchar *
pojk_menu_node_tree_get_string (GNode *tree)
{
  if (tree == NULL || tree->data == NULL)
    return NULL;
  else
    return pojk_menu_node_get_string (tree->data);
}



void
pojk_menu_node_tree_set_string (GNode       *tree,
                                  const gchar *value)
{
  PojkMenuNodeType type;

  type = pojk_menu_node_tree_get_node_type (tree);

  g_return_if_fail (type == POJK_MENU_NODE_TYPE_NAME ||
                    type == POJK_MENU_NODE_TYPE_DIRECTORY ||
                    type == POJK_MENU_NODE_TYPE_DIRECTORY_DIR ||
                    type == POJK_MENU_NODE_TYPE_APP_DIR ||
                    type == POJK_MENU_NODE_TYPE_FILENAME ||
                    type == POJK_MENU_NODE_TYPE_CATEGORY ||
                    type == POJK_MENU_NODE_TYPE_OLD ||
                    type == POJK_MENU_NODE_TYPE_NEW ||
                    type == POJK_MENU_NODE_TYPE_MENUNAME ||
                    type == POJK_MENU_NODE_TYPE_MERGE_DIR);

  pojk_menu_node_set_string (tree->data, value);
}


PojkMenuLayoutMergeType
pojk_menu_node_tree_get_layout_merge_type (GNode *tree)
{
  g_return_val_if_fail (pojk_menu_node_tree_get_node_type (tree) == POJK_MENU_NODE_TYPE_MERGE, 0);
  return ((PojkMenuNode *)tree->data)->data.layout_merge_type;
}



PojkMenuMergeFileType
pojk_menu_node_tree_get_merge_file_type (GNode *tree)
{
  g_return_val_if_fail (pojk_menu_node_tree_get_node_type (tree) == POJK_MENU_NODE_TYPE_MERGE_FILE, 0);
  return pojk_menu_node_get_merge_file_type (tree->data);
}



const gchar *
pojk_menu_node_tree_get_merge_file_filename (GNode *tree)
{
  g_return_val_if_fail (pojk_menu_node_tree_get_node_type (tree) == POJK_MENU_NODE_TYPE_MERGE_FILE, NULL);
  return pojk_menu_node_get_merge_file_filename (tree->data);
}



void
pojk_menu_node_tree_set_merge_file_filename (GNode       *tree,
                                                  const gchar *filename)
{
  g_return_if_fail (pojk_menu_node_tree_get_node_type (tree) == POJK_MENU_NODE_TYPE_MERGE_FILE);
  pojk_menu_node_set_merge_file_filename (tree->data, filename);
}



gint
pojk_menu_node_tree_compare (GNode *tree,
                               GNode *other_tree)
{
  PojkMenuNode *node;
  PojkMenuNode *other_node;

  if (tree == NULL || other_tree == NULL)
    return 0;

  node = tree->data;
  other_node = other_tree->data;

  if (node->node_type != other_node->node_type)
    return 0;

  switch (node->node_type)
    {
    case POJK_MENU_NODE_TYPE_NAME:
    case POJK_MENU_NODE_TYPE_DIRECTORY:
    case POJK_MENU_NODE_TYPE_DIRECTORY_DIR:
    case POJK_MENU_NODE_TYPE_APP_DIR:
    case POJK_MENU_NODE_TYPE_FILENAME:
    case POJK_MENU_NODE_TYPE_CATEGORY:
    case POJK_MENU_NODE_TYPE_OLD:
    case POJK_MENU_NODE_TYPE_NEW:
    case POJK_MENU_NODE_TYPE_MENUNAME:
    case POJK_MENU_NODE_TYPE_MERGE_DIR:
      return g_strcmp0 (node->data.string, other_node->data.string);
      break;

    case POJK_MENU_NODE_TYPE_MERGE_FILE:
      return g_strcmp0 (node->data.merge_file.filename,
                        other_node->data.merge_file.filename);
      break;

    default:
      return 0;
      break;
    }

  return 0;
}



GNode *
pojk_menu_node_tree_copy (GNode *tree)
{
  return g_node_copy_deep (tree, (GCopyFunc) pojk_menu_node_copy, NULL);
}



static gboolean
free_children (GNode   *tree,
               gpointer data)
{
  pojk_menu_node_tree_free_data (tree);
  return FALSE;
}



void
pojk_menu_node_tree_free (GNode *tree)
{
  if (tree != NULL)
    {
      g_node_traverse (tree, G_IN_ORDER, G_TRAVERSE_ALL, -1,
                       (GNodeTraverseFunc) free_children, NULL);

      g_node_destroy (tree);
    }
}



void
pojk_menu_node_tree_free_data (GNode *tree)
{
  if (tree != NULL && tree->data != NULL)
    g_object_unref (tree->data);
}

