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
#include "hsn.h"

int		hsn_node_setup(t_hsn_node *node,
			       const char *credentials_dirpath,
			       const char *peers_list_filepath,
			       const char *peers_dirpath,
			       int port)
{
  fprintf(stderr, "HSN node setup:\n");
  fprintf(stderr, "* Loading credentials...\n");
  if (hsn_node_load_credentials(node, credentials_dirpath) != 0)
    goto err_load_credentials;
  fprintf(stderr, "* Loading peers...\n");
  if (hsn_node_load_peers(node, peers_list_filepath, peers_dirpath) != 0)
    goto err_load_peers;
  fprintf(stderr, "* Connecting to peers...\n");
  if (hsn_node_connect_to_peers(node) != 0)
    goto err_connect_to_peers;
  fprintf(stderr, "* Starting server...\n");
  node->ssh_server.port = port;
  if (ssh_server_start(node) != 0)
    goto err_start_server;
  fprintf(stderr, "done.\n\n");
  return (0);

 err_start_server:
  hsn_node_disconnect_from_peers(node);
 err_connect_to_peers:
  hsn_node_unload_peers(node);
 err_load_peers:
  hsn_node_unload_credentials(node);
 err_load_credentials:
  return (1);
}
