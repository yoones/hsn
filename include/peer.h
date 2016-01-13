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

# include "hsn_types.h"

int		peer_init(t_peer *peer);
t_peer		*peer_alloc();
void		peer_clean(t_peer *peer);
void		peer_free(t_peer *peer);
int		peer_fill(t_peer *peer, const char *entry);
int		peer_load_credentials(t_peer *peer, const char *peers_dirpath);

/*
** peer_fill() reminder:
** entry = "uid;name;addr1:port1,addr2:port2,..."
*/

#endif
