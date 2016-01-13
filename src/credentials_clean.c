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
#include <string.h>
#include <libssh/libssh.h>
#include "hsn.h"

void		credentials_clean(t_credentials *credentials)
{
  int		i;

  ssh_key_free(credentials->public_key);
  ssh_key_free(credentials->private_key);
  ssh_clean_pubkey_hash(&(credentials->public_key_hash));
  if (credentials->public_key_filepath)
    {
      i = strlen(credentials->public_key_filepath);
      memset(credentials->public_key_filepath, 0, i);
      free(credentials->public_key_filepath);
    }
  if (credentials->private_key_filepath)
    {
      i = strlen(credentials->private_key_filepath);
      memset(credentials->private_key_filepath, 0, i);
      free(credentials->private_key_filepath);
    }
}
