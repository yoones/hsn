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
#include <libssh/server.h>
#include "hsn.h"

int		server_init(t_server *server)
{
  memset(server, 0, sizeof(t_server));
  server->port = HSN_DEFAULT_PORT;
  server->sshbind = ssh_bind_new();
  server->events = ssh_event_new();
  if (server->sshbind == NULL || server->events == NULL)
    {
      ssh_bind_free(server->sshbind);
      ssh_event_free(server->events);
      return (1);
    }
  ssh_callbacks_init(&(server->cb));
  list_init(&(server->auth_waiting_list), NULL, NULL); /* TODO: add free callback */
  return (0);
}
