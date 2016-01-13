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

static int	_extract_peer_addresses(t_peer *peer, char **addresses)
{
  t_address	*addr;

  for (int i = 0; addresses[i]; i++)
    {
      if (addresses[i][0] == '\0')
	continue ;
      addr = address_alloc();
      if (!addr
	  || address_fill(addr, addresses[i]) != 0
	  || list_push_back(&(peer->addresses), addr) != 0)
	{
	  if (addr)
	    {
	      address_clean(addr);
	      free(addr);
	    }
	  list_clear(&(peer->addresses));
	  return (1);
	}
    }
  return (0);
}

int		peer_fill(t_peer *peer, const char *entry)
{
  char		**peer_info;
  char		**addresses;

  peer_info = split(entry, ";");
  if (peer_info == NULL)
    return (1);
  if (count_wordtab_words(peer_info) != 3
      || peer_info[0] == '\0'
      || peer_info[1] == '\0'
      || peer_info[2] == '\0')
    {
      fprintf(stderr, "Invalid peer entry found\n");
      free_wordtab(peer_info);
      return (1);
    }
  addresses = split(peer_info[2], ",");
  if (addresses == NULL)
    {
      free_wordtab(peer_info);
      return (1);
    }
  peer->uid = peer_info[0];
  peer->name = peer_info[1];
  if (_extract_peer_addresses(peer, addresses) != 0)
    {
      free_wordtab(addresses);
      free_wordtab(peer_info);
      return (1);
    }
  free_wordtab(addresses);
  free(peer_info[2]);
  free(peer_info);
  return (0);
}
