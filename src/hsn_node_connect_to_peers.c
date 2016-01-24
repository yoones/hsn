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

#include <stdio.h>
#include <libssh/libssh.h>
#include "hsn.h"

int		hsn_node_connect_to_peers(t_hsn_node *node)
{
  t_lnode	*w;
  t_peer	*peer;
  t_lnode	*waddr;

  for (w = node->peers.head; w; w = w->next)
    {
      peer = w->data;
      printf("\ndebug: peer uid = %s\n", peer->uid);
      /* Skip peer if not fully loaded/ready or already connected */
      if (peer->credentials.public_key == NULL
	  || peer->connexion.connexion_origin != NOT_CONNECTED)
	continue ;
      printf("debug: trying to connect to one of peer's addresses...\n");
      for (waddr = peer->addresses.head; waddr; waddr = waddr->next)
	{
	  if (connexion_connect(node,
				peer,
				waddr->data,
				&(node->ssh_verbosity)) == 0)
	    {
	      printf("Connected to peer!\n\n");
	      return (0);
	    }
	}
    }
  printf("Peer not found\n\n");
  return (0);
}
