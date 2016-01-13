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
#include "hsn.h"

int		ssh_server_start(t_hsn_node *hsn_node)
{
  /* if (ssh_bind_options_set(hsn_node->ssh_server.sshbind, */
  /*			   SSH_BIND_OPTIONS_RSAKEY, */
  /*			   hsn_node->credentials.private_key_filepath) != 0) */
  /*   { */
  /*     fprintf(stderr, "Bind options set failed (%s)\n", */
  /*	      ssh_get_error(hsn_node->ssh_server.sshbind)); */
  /*     return (1); */
  /*   } */
  /* if (ssh_bind_listen(hsn_node->ssh_server.sshbind) != 0) */
  /*   { */
  /*     fprintf(stderr, "Bind listen failed (%s)\n", */
  /*	      ssh_get_error(hsn_node->ssh_server.sshbind)); */
  /*     return (1); */
  /*   } */
  /* ssh_bind_accept(hsn_node->ssh_server.sshbind, */
  /*		  hsn_node->ssh_server.session); */
  return (1);
}
