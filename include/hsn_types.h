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

#ifndef HSN_TYPES_H_
# define HSN_TYPES_H_

# include <libssh/libssh.h>
# include <libssh/server.h>
# include "list.h"

typedef struct		s_address
{
  char			*addr;
  int			port;
}			t_address;

typedef struct		s_credentials
{
  ssh_key		public_key;
  ssh_key		private_key;
  unsigned char		*public_key_hash;
  size_t		public_key_hash_len;
  char			*public_key_filepath;
  char			*private_key_filepath;
}			t_credentials;

typedef enum		e_connexion_origin {
  INITIATED_BY_SELF = 1,
  INITIATED_BY_PEER
}			t_connexion_origin;

typedef struct		s_connexion
{
  t_address		*address;
  t_credentials		*credentials;
  ssh_session		session;
  t_connexion_origin	connexion_origin;
}			t_connexion;

typedef struct		s_server
{
  int			port;
  ssh_bind		sshbind;
}			t_server;

typedef struct		s_hsn_node
{
  t_credentials		credentials;
  t_list		peers;
  t_server		server;
  int			ssh_verbosity;
}			t_hsn_node;

typedef struct		s_peer
{
  char			*uid;
  char			*name;
  t_credentials		credentials;
  t_list		addresses;
  t_connexion		connexion;
}			t_peer;

#endif
