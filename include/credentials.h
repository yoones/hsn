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

#ifndef CREDENTIALS_H_
# define CREDENTIALS_H_

# include <libssh/libssh.h>

typedef struct	s_credentials
{
  ssh_key	public_key;
  ssh_key	private_key;
  unsigned char	*public_key_hash;
  size_t	public_key_hash_len;
  char		*public_key_filepath;
  char		*private_key_filepath;
}		t_credentials;

void		credentials_init(t_credentials *credentials);
t_credentials	*credentials_alloc();
void		credentials_clean(t_credentials *credentials);
void		credentials_free(t_credentials *credentials);
int		credentials_load(t_credentials *credentials,
				 const char *credentials_dirpath,
				 int mode,
				 const char *password);

# define CREDENTIALS_LOAD_PRIVATE_KEY	(1 << 0)
# define CREDENTIALS_LOAD_PUBLIC_KEY	(1 << 1)
# define CREDENTIALS_LOAD_BOTH_KEYS	(CREDENTIALS_LOAD_PRIVATE_KEY | CREDENTIALS_LOAD_PUBLIC_KEY)

#endif
