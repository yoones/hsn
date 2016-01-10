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

/*
** NOTE:
** Gets a set of characters and looks for the first
** occurence of any of them in str.
*/
int		find_char(char *str, char *look_for)
{
  int		i;
  int		j;

  for (i = 0; str[i]; i++)
    {
      for (j = 0; look_for[j]; j++)
	{
	  if (str[i] == look_for[j])
	    return (i);
	}
    }
  return (-1);
}
