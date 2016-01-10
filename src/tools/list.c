/*
** This file is part of HSN (Human-Scale Network)
**
** HSN: secure, distributed, SPOF-free network of trust
** Copyright (C) 2016 Younes SERRAJ
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** version 2 as published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
** or see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <stdlib.h>
#include "list.h"

/*
  Initializes a list
 */
void		list_init(t_list *list,
			  t_list_data_free *f_free,
			  t_list_data_cmp *f_cmp)
{
  memset(list, '\0', sizeof(t_list));
  list->f_free = f_free;
  list->f_cmp = f_cmp;
}

/*
  Allocates and initializes a new list
 */
t_list		*list_create(t_list_data_free *f_free,
			     t_list_data_cmp *f_cmp)
{
  t_list	*list;

  list = malloc(sizeof(t_list));
  if (!list)
    return (NULL);
  list_init(list, f_free, f_cmp);
  return (list);
}

/*
  Pops all nodes in (list)
  If (fptr) is set, it is called on every node's data to free it
 */
void		list_clear(t_list *list)
{
  if (!list->f_free)
    while (list->size > 0)
      list_pop_front(list);
  else
    while (list->size > 0)
      {
	list->f_free(list->head->data);
	list_pop_front(list);
      }
}

/*
  Initializes a node
 */
void		lnode_init(t_lnode *node,
			   void *data, t_lnode *prev, t_lnode *next)
{
  node->data = data;
  node->prev = prev;
  node->next = next;
}

/*
  Allocates and initializes a new node
 */
t_lnode		*lnode_create(void *data, t_lnode *prev, t_lnode *next)
{
  t_lnode	*node;

  node = malloc(sizeof(t_lnode));
  if (!node)
    return (NULL);
  lnode_init(node, data, prev, next);
  return (node);
}

/*
  Adds node with (data) at the beginning of (list)
  Returns 0 on success
  Returns -1 on failure
*/
int		list_push_front(t_list *list, void *data)
{
  t_lnode	*node;

  if (!(node = malloc(sizeof(t_lnode))))
    return (-1);
  node->data = data;
  node->prev = NULL;
  node->next = list->head;
  if (list->head)
    list->head->prev = node;
  list->head = node;
  if (!list->tail)
    list->tail = node;
  list->size++;
  return (0);
}

/*
  If (list) is empty, calls list_push().
  Otherwise, adds node with (data) at the end of (list)
  Returns 0 on success
  Returns -1 on failure
*/
int		list_push_back(t_list *list, void *data)
{
  t_lnode	*node;

  if (list->size == 0)
    return (list_push_front(list, data));
  if (!(node = malloc(sizeof(t_lnode))))
    return (-1);
  node->data = data;
  node->prev = list->tail;
  node->next = NULL;
  list->tail->next = node;
  list->tail = node;
  list->size++;
  return (0);
}

/*
  If (list) is not empty,
  Frees first node of (list)
  Expects data to be already freed
 */
void		list_pop_front(t_list *list)
{
  t_lnode	*node;

  if (list->size > 0)
    {
      node = list->head;
      list->head = node->next;
      if (list->head)
	list->head->prev = NULL;
      free(node);
      list->size--;
    }
  if (!list->size)
    {
      list->head = NULL;
      list->tail = NULL;
    }
}

/*
  If (list) is not empty,
  Frees last node of (list)
  Expects data to be already freed
 */
void		list_pop_back(t_list *list)
{
  t_lnode	*node;

  if (list->size < 2)
    {
      list_pop_front(list);
      return ;
    }
  node = list->tail;
  list->tail = node->prev;
  if (list->tail)
    list->tail->next = NULL;
  free(node);
  list->size--;
}

void		list_pop_node(t_list *list, t_lnode *node)
{
  t_lnode	*w;

  if (list->size < 3)
    {
      if (list->head == node)
	list_pop_front(list);
      else if (list->tail == node)
	list_pop_back(list);
    }
  else
    {
      for (w = list->head; w != NULL; w = w->next)
	{
	  if (w == node)
	    {
	      node->prev->next = node->next;
	      node->next->prev = node->prev;
	      list->size--;
	      free(node);
	      return ;
	    }
	}
    }
}

void		list_pop_data(t_list *list, void *data)
{
  t_lnode	*w;

  if (list->size < 3)
    {
      if (list->head && list->head->data == data)
	list_pop_front(list);
      else if (list->tail && list->tail->data == data)
	list_pop_back(list);
    }
  else
    {
      for (w = list->head; w != NULL; w = w->next)
	{
	  if (w->data == data)
	    {
	      w->prev->next = w->next;
	      w->next->prev = w->prev;
	      list->size--;
	      free(w);
	      return ;
	    }
	}
    }
}

/*
  Compares data using (list->f_cmp)
  Returns 0 on success
  Returns -1 on failure or if no comparison function is set (list->f_cmp)
 */
int		list_contains(t_list *list, void *data)
{
  t_lnode	*w;

  if (!list->f_cmp)
    return (-1);
  w = list->head;
  while (w && list->f_cmp(w->data, data))
    w = w->next;
  return (w ? 0 : -1);
}
