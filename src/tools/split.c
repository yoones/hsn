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
#include <string.h>
#include <stdlib.h>

static int	_is_sep(const char c, const char *sep)
{
  int		i;

  for (i = 0; sep[i]; i++)
    {
      if (sep[i] == c)
	return (1);
    }
  return (sep[i] == c ? 1 : 0);
}

static int	_count_words(const char *data, const char *sep)
{
  int		i;
  int		nb;

  if (*data == '\0')
    return (0);
  nb = 1;
  for (i = 0; data[i]; i++)
    {
      if (_is_sep(data[i], sep) == 1)
	nb++;
    }
  return (nb);
}

static void	_skip_word(const char **data, const char *sep)
{
  while (**data && _is_sep(**data, sep) == 0)
    (*data)++;
  if (_is_sep(**data, sep))
    (*data)++;
}

static char	*_extract_word(const char *data, const char *sep)
{
  char		*word;
  int		len;

  for (len = 0; _is_sep(data[len], sep) == 0; len++)
    ;
  word = malloc(sizeof(char) * (len + 1));
  if (!word)
    {
      perror("malloc");
      return (NULL);
    }
  memcpy(word, data, len);
  word[len] = '\0';
  return (word);
}

char		**split(const char *data, const char *sep)
{
  int		nb_words;
  char		**words;
  int		i;

  nb_words = _count_words(data, sep);
  words = malloc(sizeof(char *) * (nb_words + 1));
  if (!words)
    {
      perror("malloc");
      return (NULL);
    }
  for (i = 0; i < nb_words; i++)
    {
      words[i] = _extract_word(data, sep);
      if (!(words[i]))
	{
	  perror("malloc");
	  while (i > 0)
	    {
	      free(words[i - 1]);
	      i--;
	    }
	  free(words);
	  return (NULL);
	}
      _skip_word(&data, sep);
    }
  words[i] = NULL;
  return (words);
}

void		free_wordtab(char **wt)
{
  int		i;

  if (!wt)
    return ;
  for (i = 0; wt[i]; i++)
    free(wt[i]);
  free(wt);
}

int		count_wordtab_words(char **wt)
{
  int		i;

  for (i = 0; wt[i]; i++)
    ;
  return (i);
}
