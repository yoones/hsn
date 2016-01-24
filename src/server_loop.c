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
#include <libssh/callbacks.h>
#include "hsn.h"

/*
** TODO:
** - set ssh_bind callbacks
** - put ssh_bind in non-blocking mode ??
** - call ssh_*_poll() on ssh_bind to know when to call _accept_new_client()
** - catch SIGUSR1 to stop the main loop
*/

static t_peer	*_get_owner_of_public_key(t_hsn_node *hsn_node, ssh_key pubkey)
{
  t_lnode	*w;
  t_peer	*peer;

  for (w = hsn_node->peers.head; w; w = w->next)
    {
      peer = w->data;
      if (ssh_key_cmp(peer->credentials.public_key,
		      pubkey,
		      SSH_KEY_CMP_PUBLIC) == 0)
	return (peer);
    }
  return (NULL);
}

static int	_my_ssh_auth_pubkey_callback(ssh_session session,
					     __attribute__((unused)) const char *user,
					     struct ssh_key_struct *pubkey,
					     __attribute__((unused)) char signature_state,
					     void *userdata)
{
  t_hsn_node	*hsn_node;
  t_peer	*peer;

  hsn_node = userdata;
  list_pop_data(&(hsn_node->server.auth_waiting_list), session);
  peer = _get_owner_of_public_key(hsn_node, pubkey);
  if (!peer)
    {
      ssh_event_remove_session(hsn_node->server.events, session);
      ssh_disconnect(session);
      ssh_free(session);
      return (-1);
    }
  ssh_free(peer->connexion.session);
  peer->connexion.session = session;
  peer->connexion.connexion_origin = INITIATED_BY_PEER;
  return (0);
}

static int	_start_client_authentication(t_hsn_node *hsn_node,
					     ssh_session new_client_session)
{
  ssh_set_server_callbacks(new_client_session, &(hsn_node->server.cb));
  ssh_set_auth_methods(new_client_session, SSH_AUTH_METHOD_PUBLICKEY);
  if (ssh_handle_key_exchange(new_client_session) != 0)
    {
      fprintf(stderr, "ssh_handle_key_exchange() failed (%s)\n", ssh_get_error(new_client_session));
      return (1);
    }
  ssh_event_add_session(hsn_node->server.events, new_client_session);
  return (0);
}

static int	_accept_new_client(t_hsn_node *hsn_node)
{
  ssh_session	new_client_session;

  new_client_session = ssh_new();
  if (new_client_session == NULL)
    {
      fprintf(stderr, "Memory exhausted\n");
      return (1);
    }
  if (ssh_bind_accept(hsn_node->server.sshbind, new_client_session) == SSH_ERROR)
    {
      fprintf(stderr, "Failed to accept a new client (%s)\n",
	      ssh_get_error(hsn_node->server.sshbind));
      goto err;
    }
  if (_start_client_authentication(hsn_node, new_client_session) != 0)
    goto err;
  if (list_push_back(&(hsn_node->server.auth_waiting_list), new_client_session) != 0)
    {
      fprintf(stderr, "Memory exhausted\n");
      goto err;
    }
  return (0);

 err:
  ssh_disconnect(new_client_session);
  ssh_free(new_client_session);
  return (1);
}

static int	_prepare_callbacks_structure(t_hsn_node *hsn_node)
{
  ssh_callbacks_init(&(hsn_node->server.cb));
  hsn_node->server.cb.userdata = hsn_node;
  hsn_node->server.cb.auth_pubkey_function = _my_ssh_auth_pubkey_callback;
  return (0);
}

int		server_loop(t_hsn_node *hsn_node)
{
  _prepare_callbacks_structure(hsn_node);
  if (_accept_new_client(hsn_node) != 0)
    {
      fprintf(stderr, "Failed to accept new client\n");
      goto err;
    }
  while (ssh_event_dopoll(hsn_node->server.events, -1) != SSH_ERROR)
    ;
  /* TODO: remove disconnected peer from event and loop again */
  return (0);

 err:
  /* do some cleaning */
  return (1);
}
