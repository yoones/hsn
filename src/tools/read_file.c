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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		read_file(char *filepath, char **data)
{
  struct stat	st;
  int		fd;
  int		i;
  char		*w;
  int		rsize;

  if (stat(filepath, &st))
    {
      perror("stat");
      return (1);
    }
  else if (st.st_size == 0)
    {
      dprintf(2, "file seems empty\n");
      return (1);
    }
  fd = open(filepath, O_RDONLY);
  if (fd == -1)
    {
      perror("open");
      return (1);
    }
  *data = malloc(sizeof(char) * (st.st_size + 1));
  if (!(*data))
    {
      perror("malloc");
      close(fd);
      return (1);
    }
  w = *data;
  i = 0;
  rsize = st.st_size;
  do
    {

      i = read(fd, w, rsize);
      if (i == -1)
	{
	  perror("read");
	  close(fd);
	  free(*data);
	  return (1);
	}
      w += i;
      rsize -= i;
    } while (i > 0);
  *w = '\0';
  close(fd);
  return (0);
}
