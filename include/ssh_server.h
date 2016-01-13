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

#ifndef SSH_SERVER_H_
# define SSH_SERVER_H_

# include <libssh/libssh.h>
# include <libssh/server.h>
# include "address.h"

typedef struct		s_ssh_server
{
  int			port;
  ssh_bind		sshbind;
  ssh_session		session;
}			t_ssh_server;

int		ssh_server_init(t_ssh_server *ssh_server);
t_ssh_server	*ssh_server_alloc();
void		ssh_server_clean(t_ssh_server *ssh_server);
void		ssh_server_free(t_ssh_server *ssh_server);

#endif
