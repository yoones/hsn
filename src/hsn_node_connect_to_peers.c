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
#include "hsn_node.h"
#include "peer.h"
#include "xfunctions.h"
#include "list.h"
#include "ssh_client.h"

int		hsn_node_connect_to_peers(t_hsn_node *node)
{
  t_lnode	*w;
  t_peer	*peer;
  t_lnode	*waddr;
  t_address	*address;

  for (w = node->peers.head; w; w = w->next)
    {
      peer = w->data;
      /* Skip peer if not fully loaded/ready */
      if (peer->credentials.public_key == NULL
	  || peer->credentials.public_key_hash == NULL)
	continue ;
      /* Skip peer if already connected */
      if (peer->ssh_client.address != NULL)
	continue ;
      for (waddr = peer->addresses.head; waddr; waddr = waddr->next)
	{
	  address = waddr->data;
	  if (ssh_client_try_connect(&(peer->ssh_client),
				     address,
				     &(node->ssh_verbosity)) == 0)
	    break ;
	}
    }
  return (0);
}
