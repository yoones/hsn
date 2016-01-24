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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hsn.h"

int		main(int argc, char **argv)
{
  t_hsn_node	hsn_node;
  int		port;

  port = argc == 2 ? atoi(argv[1]) : HSN_DEFAULT_PORT;
  hsn_node_init(&hsn_node);
  if (hsn_node_setup(&hsn_node,
		     HSN_DEFAULT_CREDENTIALS_DIRPATH,
		     HSN_DEFAULT_PEERS_LIST_FILEPATH,
		     HSN_DEFAULT_PEERS_DIRPATH,
		     port) != 0)
    {
      fprintf(stderr, "Failed to setup a HSN node. Aborting.\n");
      return (EXIT_FAILURE);
    }
  hsn_node_print_status(&hsn_node);

  /* sleep(3); */
  server_loop(&hsn_node);
  
  hsn_node_clean(&hsn_node);
  ssh_finalize();
  fprintf(stderr, "Goodbye\n");
  return (EXIT_SUCCESS);
}
