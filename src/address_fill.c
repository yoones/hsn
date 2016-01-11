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
#include "address.h"
#include "tools.h"
#include "hsn_node.h"

int		address_fill(t_address *address, const char *source)
{
  char		**fields;

  if (source[0] == '\0')
    return (1);
  fields = split(source, ":");
  if (!fields)
    return (1);
  switch (count_wordtab_words(fields))
    {
    case (1):
      address->addr = fields[0];
      address->port = HSN_DEFAULT_PORT;
      break ;
    case (2):
      address->addr = fields[0];
      address->port = atoi(fields[1]);
      if (address->port < 1)
	{
	  fprintf(stderr, "Invalid peer entry found (port < 1)\n");
	  free_wordtab(fields);
	  return (1);
	}
      free(fields[1]);
      break ;
    default:
      fprintf(stderr, "Invalid peer entry found (more than 2 fields found for address)\n");
      free_wordtab(fields);
      return (1);
    }
  free(fields);
  return (0);
}
