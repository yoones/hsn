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
#include "hsn_node.h"
#include "peer.h"
#include "ssh_server.h"

void		hsn_node_init(t_hsn_node *node)
{
  credentials_init(&(node->credentials));
  list_init(&(node->peers), (t_list_data_free *)peer_free, NULL);
  /* ssh_server_init(&(node->ssh_server)); */
  node->ssh_verbosity = HSN_DEFAULT_SSH_VERBOSITY;
}
