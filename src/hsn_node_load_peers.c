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
#include <stdio.h>
#include "hsn_node.h"
#include "tools.h"
#include "peer.h"

static int	_extract_peers_from_list(t_hsn_node *node, char **peers_list)
{
  t_peer	*peer;

  for (int i = 0; peers_list[i]; i++)
    {
      if (peers_list[i][0] == '\0')
	continue ;
      peer = peer_alloc();
      if (!peer
	  || peer_fill(peer, peers_list[i]) != 0
	  || list_push_back(&(node->peers), peer) != 0)
	{
	  if (peer)
	    {
	      peer_clean(peer);
	      free(peer);
	    }
	  hsn_node_unload_peers(node);
	  return (1);
	}
    }
  return (0);
}

static int	_check_peers_uid_uniqueness(t_list *peers)
{
  t_lnode	*w1, *w2;
  t_peer	*p1, *p2;

  for (w1 = peers->head; w1->next; w1 = w1->next)
    {
      p1 = w1->data;
      for (w2 = w1->next; w2; w2 = w2->next)
	{
	  p2 = w2->data;
	  if (!strcmp(p1->uid, p2->uid))
	    {
	      fprintf(stderr, "Invalid peers list (found duplicated uids)\n");
	      return (1);
	    }
	}
    }
  return (0);
}

static int	_check_peers_uid_validity(t_list *peers)
{
  t_lnode	*w;
  t_peer	*p;
  char		*wbuf;

  for (w = peers->head; w; w = w->next)
    {
      p = w->data;
      wbuf = p->uid;
      while ((*wbuf >= 'a' && *wbuf <= 'z')
	      || (*wbuf >= 'A' && *wbuf <= 'Z')
	      || (*wbuf >= '0' && *wbuf <= '9')
	      || *wbuf == '_')
	wbuf++;
      if (*wbuf)
	{
	  fprintf(stderr, "Invalid peers list (found an invalid peer uid).\n");
	  return (1);
	}
    }
  return (0);
}

static int	_load_peers_credentials(t_list *peers, const char *peers_dirpath)
{
  t_lnode	*w;
  t_peer	*p;

  for (w = peers->head; w; w = w->next)
    {
      p = w->data;
      if (peer_load_credentials(p, peers_dirpath) != 0)
	return (1);
    }
  return (0);
}

int		hsn_node_load_peers(t_hsn_node *node,
				    const char *peers_list_filepath,
				    const char *peers_dirpath)
{
  char		*data;
  char		**peers_list;
  int		ret;

  if (access(peers_list_filepath, R_OK) != 0)
    {
      fprintf(stderr, "Failed to access peers list\n");
      return (1);
    }
  if (read_file(peers_list_filepath, &data) != 0)
    return (1);
  peers_list = split(data, "\n");
  free(data);
  if (!peers_list)
    return (1);
  ret = _extract_peers_from_list(node, peers_list);
  free_wordtab(peers_list);
  if (ret != 0)
    return (1);
  if (_check_peers_uid_uniqueness(&(node->peers)) != 0
      || _check_peers_uid_validity(&(node->peers)) != 0
      || _load_peers_credentials(&(node->peers), peers_dirpath) != 0)
    {
      hsn_node_unload_peers(node);
      return (1);
    }
  return (ret == 0 ? 0 : 1);
}
