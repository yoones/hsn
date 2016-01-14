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
#include <libssh/libssh.h>
#include "hsn.h"

static int	_authenticate_self(t_peer *peer)
{
  if ((ssh_userauth_list(peer->ssh_client.session, NULL)
       & SSH_AUTH_METHOD_PUBLICKEY) == 0)
    {
      fprintf(stderr, "Peer doesn't accept public key authentication\n");
      return (1);
    }
  if (ssh_userauth_publickey(peer->ssh_client.session,
			     NULL,
			     peer->credentials.private_key) != SSH_AUTH_SUCCESS)
    {
      fprintf(stderr, "Failed to authenticate\n");
      return (1);
    }
  return (0);
}

static int	_check_peer_credentials(t_peer *peer)
{
  t_credentials	credentials;

  credentials_init(&credentials);
  if (ssh_get_publickey(peer->ssh_client.session,
			&(credentials.public_key)) != SSH_OK)
    {
      fprintf(stderr, "Failed to get peer's public key\n");
      goto err;
    }
  if (ssh_key_cmp(peer->credentials.public_key,
		  credentials.public_key,
		  SSH_KEY_CMP_PUBLIC) != 0)
    {
      fprintf(stderr, "Peer's public key doesn't match\n");
      goto err;
    }
  credentials_clean(&credentials);
  return (0);

 err:
  credentials_clean(&credentials);
  return (1);
}

int		ssh_client_connect(t_peer *peer,
				   t_address *address,
				   int *verbosity)
{
  if (peer->ssh_client.session == NULL
      || peer->ssh_client.address != NULL)
    return (1);
  ssh_options_set(peer->ssh_client.session, SSH_OPTIONS_HOST, address->addr);
  ssh_options_set(peer->ssh_client.session, SSH_OPTIONS_PORT, &(address->port));
  ssh_options_set(peer->ssh_client.session, SSH_OPTIONS_LOG_VERBOSITY, verbosity);
  if (ssh_connect(peer->ssh_client.session) != SSH_OK)
    return (-1);
  if (_check_peer_credentials(peer) != 0)
    {
      fprintf(stderr, "Warning: failed to check peer's credentials\n");
      ssh_disconnect(peer->ssh_client.session);
      return (1);
    }
  if (_authenticate_self(peer) != 0)
    {
      fprintf(stderr, "Warning: failed to authenticate\n");
      ssh_disconnect(peer->ssh_client.session);
      return (1);
    }
  peer->ssh_client.address = address;
  peer->ssh_client.credentials = &(peer->credentials);
  return (0);
}
