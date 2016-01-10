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

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void		*xmalloc(size_t size)
{
  void		*ret;

  ret = malloc(size);
  if (!ret)
    perror("malloc");
  return (ret);
}

void		*xrealloc(void *ptr, size_t size)
{
  void		*ret;

  ret = realloc(ptr, size);
  if (!ret)
    perror("realloc");
  return (ret);
}

void		*xcalloc(size_t nmemb, size_t size)
{
  void		*ret;

  ret = calloc(nmemb, size);
  if (!ret)
    perror("calloc");
  return (ret);
}

char		*xstrdup(const char *s)
{
  char		*ret;

  ret = strdup(s);
  if (!ret)
    perror("strdup");
  return (ret);
}

char		*xstrndup(const char *s, size_t n)
{
  char		*ret;

  ret = strndup(s, n);
  if (!ret)
    perror("strndup");
  return (ret);
}
