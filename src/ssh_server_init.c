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

#include <string.h>
#include <libssh/libssh.h>
#include "ssh_server.h"
#include "hsn_node.h"
#include "address.h"

int		ssh_server_init(t_ssh_server *ssh_server)
{
  memset(ssh_server, 0, sizeof(t_ssh_server));
  ssh_server->port = HSN_DEFAULT_PORT;
  ssh_server->session = ssh_new();
  ssh_server->sshbind = ssh_bind_new();
  if (ssh_server->session == NULL || ssh_server->sshbind == NULL)
    {
      ssh_free(ssh_server->session);
      ssh_bind_free(ssh_server->sshbind);
      return (1);
    }
  return (0);
}
