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
#include "ssh_client.h"
#include "tools.h"
#include "address.h"

int		ssh_client_try_connect(t_ssh_client *ssh_client,
				       t_address *address,
				       int *verbosity)
{
  if (ssh_client->session == NULL || ssh_client->address != NULL)
    return (1);
  ssh_options_set(ssh_client->session, SSH_OPTIONS_HOST, address->addr);
  ssh_options_set(ssh_client->session, SSH_OPTIONS_PORT, &(address->port));
  ssh_options_set(ssh_client->session, SSH_OPTIONS_LOG_VERBOSITY, verbosity);
  if (ssh_connect(ssh_client->session) != SSH_OK)
    return (-1);
  /* TODO: client/server authentication */
  ssh_client->address = address;
  return (0);
}
