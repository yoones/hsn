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

#ifndef ADDRESS_H_
# define ADDRESS_H_

typedef struct	s_address
{
  char		*addr;
  int		port;
}		t_address;

void		address_init(t_address *address);
t_address	*address_alloc();
void		address_clear(t_address *address);
int		address_fill(t_address *address, char *source); /* source = "addr:port" */

#endif
