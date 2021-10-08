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

#ifndef __POJK_MENU_NODE_H__
#define __POJK_MENU_NODE_H__

#include <pojk/pojk.h>

G_BEGIN_DECLS

/* Types for the menu nodes */
typedef enum
{
  POJK_MENU_NODE_TYPE_INVALID,
  POJK_MENU_NODE_TYPE_MENU,
  POJK_MENU_NODE_TYPE_NAME,
  POJK_MENU_NODE_TYPE_DIRECTORY,
  POJK_MENU_NODE_TYPE_DIRECTORY_DIR,
  POJK_MENU_NODE_TYPE_DEFAULT_DIRECTORY_DIRS,
  POJK_MENU_NODE_TYPE_APP_DIR,
  POJK_MENU_NODE_TYPE_DEFAULT_APP_DIRS,
  POJK_MENU_NODE_TYPE_ONLY_UNALLOCATED,
  POJK_MENU_NODE_TYPE_NOT_ONLY_UNALLOCATED,
  POJK_MENU_NODE_TYPE_DELETED,
  POJK_MENU_NODE_TYPE_NOT_DELETED,
  POJK_MENU_NODE_TYPE_INCLUDE,
  POJK_MENU_NODE_TYPE_EXCLUDE,
  POJK_MENU_NODE_TYPE_ALL,
  POJK_MENU_NODE_TYPE_FILENAME,
  POJK_MENU_NODE_TYPE_CATEGORY,
  POJK_MENU_NODE_TYPE_OR,
  POJK_MENU_NODE_TYPE_AND,
  POJK_MENU_NODE_TYPE_NOT,
  POJK_MENU_NODE_TYPE_MOVE,
  POJK_MENU_NODE_TYPE_OLD,
  POJK_MENU_NODE_TYPE_NEW,
  POJK_MENU_NODE_TYPE_DEFAULT_LAYOUT,
  POJK_MENU_NODE_TYPE_LAYOUT,
  POJK_MENU_NODE_TYPE_MENUNAME,
  POJK_MENU_NODE_TYPE_SEPARATOR,
  POJK_MENU_NODE_TYPE_MERGE,
  POJK_MENU_NODE_TYPE_MERGE_FILE,
  POJK_MENU_NODE_TYPE_MERGE_DIR,
  POJK_MENU_NODE_TYPE_DEFAULT_MERGE_DIRS,
} PojkMenuNodeType;



typedef enum
{
  POJK_MENU_LAYOUT_MERGE_MENUS,
  POJK_MENU_LAYOUT_MERGE_FILES,
  POJK_MENU_LAYOUT_MERGE_ALL,
} PojkMenuLayoutMergeType;

typedef enum
{
  POJK_MENU_MERGE_FILE_PATH,
  POJK_MENU_MERGE_FILE_PARENT,
} PojkMenuMergeFileType;



typedef union  _PojkMenuNodeData  PojkMenuNodeData;
typedef struct _PojkMenuNodeClass PojkMenuNodeClass;
typedef struct _PojkMenuNode      PojkMenuNode;

#define POJK_TYPE_MENU_NODE            (pojk_menu_node_get_type ())
#define POJK_MENU_NODE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POJK_TYPE_MENU_NODE, PojkMenuNode))
#define POJK_MENU_NODE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POJK_TYPE_MENU_NODE, PojkMenuNodeClass))
#define POJK_IS_MENU_NODE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POJK_TYPE_MENU_NODE))
#define POJK_IS_MENU_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POJK_TYPE_MENU_NODE)
#define POJK_MENU_NODE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), POJK_TYPE_MENU_NODE, PojkMenuNodeClass))

GType                     pojk_menu_node_type_get_type                (void);
GType                     pojk_menu_node_get_type                     (void) G_GNUC_CONST;

PojkMenuNode           *pojk_menu_node_new                          (PojkMenuNodeType      node_type) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
PojkMenuNodeType        pojk_menu_node_get_node_type                (PojkMenuNode         *node);
PojkMenuNode           *pojk_menu_node_create                       (PojkMenuNodeType      node_type,
                                                                         gpointer                first_value,
                                                                         ...) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
PojkMenuNode           *pojk_menu_node_copy                         (PojkMenuNode         *node,
                                                                         gpointer                data) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
const gchar              *pojk_menu_node_get_string                   (PojkMenuNode         *node);
void                      pojk_menu_node_set_string                   (PojkMenuNode         *node,
                                                                         const gchar            *value);
PojkMenuMergeFileType   pojk_menu_node_get_merge_file_type          (PojkMenuNode         *node);
void                      pojk_menu_node_set_merge_file_type          (PojkMenuNode         *node,
                                                                         PojkMenuMergeFileType type);
const gchar              *pojk_menu_node_get_merge_file_filename      (PojkMenuNode         *node);
void                      pojk_menu_node_set_merge_file_filename      (PojkMenuNode         *node,
                                                                         const gchar            *filename);

GNode                    *pojk_menu_node_tree_get_child_node          (GNode                  *tree,
                                                                         PojkMenuNodeType      type,
                                                                         gboolean                reverse);
GList                    *pojk_menu_node_tree_get_child_nodes         (GNode                  *tree,
                                                                         PojkMenuNodeType      type,
                                                                         gboolean                reverse);
GList                    *pojk_menu_node_tree_get_string_children     (GNode                  *tree,
                                                                         PojkMenuNodeType      type,
                                                                         gboolean                reverse);
gboolean                  pojk_menu_node_tree_get_boolean_child       (GNode                  *tree,
                                                                         PojkMenuNodeType      type);
const gchar              *pojk_menu_node_tree_get_string_child        (GNode                  *tree,
                                                                         PojkMenuNodeType      type);
gboolean                  pojk_menu_node_tree_rule_matches            (GNode                  *tree,
                                                                         PojkMenuItem         *item);
PojkMenuNodeType        pojk_menu_node_tree_get_node_type           (GNode                  *tree);
const gchar              *pojk_menu_node_tree_get_string              (GNode                  *tree);
void                      pojk_menu_node_tree_set_string              (GNode                  *tree,
                                                                         const gchar            *value);
PojkMenuLayoutMergeType pojk_menu_node_tree_get_layout_merge_type   (GNode                  *tree);
PojkMenuMergeFileType   pojk_menu_node_tree_get_merge_file_type     (GNode                  *tree);
const gchar              *pojk_menu_node_tree_get_merge_file_filename (GNode                  *tree);
void                      pojk_menu_node_tree_set_merge_file_filename (GNode                  *tree,
                                                                         const gchar            *filename);
gint                      pojk_menu_node_tree_compare                 (GNode                  *tree,
                                                                         GNode                  *other_tree);
GNode                    *pojk_menu_node_tree_copy                    (GNode                  *tree);
void                      pojk_menu_node_tree_free                    (GNode                  *tree);
void                      pojk_menu_node_tree_free_data               (GNode                  *tree);


G_END_DECLS

#endif /* !__POJK_MENU_NODE_H__ */
