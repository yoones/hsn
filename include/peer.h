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

#ifndef PEER_H_
# define PEER_H_

# include "list.h"
# include "address.h"
# include "ssh_client.h"

typedef struct		s_peer
{
  char			*uid;
  char			*name;
  t_credentials		credentials;
  t_list		addresses;
  t_ssh_client		ssh_client;
}			t_peer;

void		peer_init(t_peer *peer);
t_peer		*peer_alloc();
void		peer_clear(t_peer *peer);
int		peer_load(t_peer *peer, char *peers_dirpath, char *peer_uid);

#endif
