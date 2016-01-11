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

#ifndef HSN_NODE_H_
# define HSN_NODE_H_

# include "list.h"
# include "credentials.h"
# include "ssh_server.h"

typedef struct	s_hsn_node
{
  t_credentials	credentials;
  t_list	peers;
  t_ssh_server	ssh_server;
}		t_hsn_node;

void		hsn_node_init(t_hsn_node *node);
t_hsn_node	*hsn_node_alloc();
void		hsn_node_clean(t_hsn_node *node);
int		hsn_node_load_credentials(t_hsn_node *node,
					  const char *credentials_dirpath);
void		hsn_node_unload_credentials(t_hsn_node *node);
int		hsn_node_load_peers(t_hsn_node *node,
				    const char *peers_list_filepath,
				    const char *peers_dirpath);
void		hsn_node_unload_peers(t_hsn_node *node);
int		hsn_node_connect_to_peers(t_hsn_node *node);
int		hsn_node_disconnect_from_peers(t_hsn_node *node);
int		hsn_node_start_server(t_hsn_node *node, int port);
int		hsn_node_stop_server(t_hsn_node *node);

int		hsn_node_setup(t_hsn_node *node,
			       const char *credentials_dirpath,
			       const char *peers_list_filepath,
			       const char *peers_dirpath,
			       int port);

# define HSN_DEFAULT_PORT			0x7c0 /* 1984 */
# define HSN_DEFAULT_CREDENTIALS_DIRPATH	"./data/self/credentials/"
# define HSN_DEFAULT_PEERS_LIST_FILEPATH	"./data/peers/peers.list"
# define HSN_DEFAULT_PEERS_DIRPATH		"./data/peers/"

#endif
