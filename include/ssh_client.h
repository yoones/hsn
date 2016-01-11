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

#ifndef SSH_CLIENT_H_
# define SSH_CLIENT_H_

# include <libssh/libssh.h>
# include "address.h"

typedef struct		s_ssh_client
{
  t_address		*address;
  ssh_session		session;
}			t_ssh_client;

void		ssh_client_init(t_ssh_client *ssh_client);
t_ssh_client	*ssh_client_alloc();
void		ssh_client_clean(t_ssh_client *ssh_client);
void		ssh_client_free(t_ssh_client *ssh_client);
int		ssh_client_try_connect(t_ssh_client *ssh_client, t_address *address);

#endif
