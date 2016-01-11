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

#include <stdlib.h>
#include <stdio.h>
#include "peer.h"
#include "tools.h"
#include "address.h"

int		peer_init(t_peer *peer)
{
  peer->uid = NULL;
  peer->name = NULL;
  credentials_init(&(peer->credentials));
  list_init(&(peer->addresses), (t_list_data_free *)address_free, NULL);
  if (ssh_client_init(&(peer->ssh_client)) != 0)
    return (1);
  return (0);
}
