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
#include <stdlib.h>
#include "hsn_node.h"
#include "peer.h"

void		hsn_node_print_status(t_hsn_node *hsn_node)
{
  int		nb_peers_connexions;
  t_lnode	*w;
  t_peer	*peer;

  nb_peers_connexions = 0;
  for (w = hsn_node->peers.head; w; w = w->next)
    {
      peer = w->data;
      if (peer->ssh_client.address)
	nb_peers_connexions++;
    }
  fprintf(stderr,
	  "[HSN node status]\n"
	  "| pid   : % 6d\n"
	  "| port  : % 6d\n"
	  "| peers : % 6d\n"
	  "|\n"
	  "| connected to %d peers\n"
	  "| server running : %s\n"
	  "+---\n",
	  getpid(),
	  HSN_DEFAULT_PORT,
	  hsn_node->peers.size,
	  nb_peers_connexions,
	  (hsn_node->ssh_server.session != NULL ? "yes" : "no"));
}
