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
#include <errno.h>
#include <libssh/libssh.h>
#include <stdlib.h>
#include "credentials.h"
#include "hsn_node.h"
#include "xfunctions.h"

static int	_import_private_key(t_credentials *credentials,
				    const char *credentials_dirpath,
				    char *buf,
				    const char *password)
{
  sprintf(buf, "%s/id_rsa", credentials_dirpath);
  if (access(buf, R_OK) != 0)
    {
      dprintf(2, "Failed to access private key (%s)\n", strerror(errno));
      return (1);
    }
  if (ssh_pki_import_privkey_file(buf,
				  password,
				  NULL,
				  NULL,
				  &(credentials->private_key)) != SSH_OK)
    {
      dprintf(2, "Failed to import private key (incorrect password or invalid file)\n");
      return (1);
    }
  return (0);
}

static int	_import_public_key(t_credentials *credentials,
				   const char *credentials_dirpath,
				   char *buf)
{
  sprintf(buf, "%s/id_rsa.pub", credentials_dirpath);
  if (access(buf, R_OK) != 0)
    {
      dprintf(2, "Failed to access public key (%s)\n", strerror(errno));
      return (1);
    }
  if (ssh_pki_import_pubkey_file(buf, &(credentials->public_key)) != SSH_OK)
    {
      dprintf(2, "Failed to import public key\n");
      ssh_key_free(credentials->public_key);
      return (1);
    }
  return (0);
}

static int	_check_mode_bits(int mode)
{
  if (mode == 0 || (mode & ~CREDENTIALS_LOAD_BOTH_KEYS) != 0)
    {
      dprintf(2, "Invalid credentials loading mode\n");
      return (1);
    }
  return (0);
}

int		credentials_load(t_credentials *credentials,
				 const char *credentials_dirpath,
				 int mode,
				 const char *password)
{
  char		*buf;
  int		buf_length;

  if (_check_mode_bits(mode) != 0)
    return (1);
  /* TODO: make sure above functions look for files named "id_rsa" */
  buf_length = strlen(credentials_dirpath) + 12;
  buf = xmalloc(sizeof(char) * buf_length);
  if (!buf)
    return (1);
  if ((mode & CREDENTIALS_LOAD_PRIVATE_KEY) != 0
      && _import_private_key(credentials,
			     credentials_dirpath,
			     buf,
			     password) != 0)
    {
      memset(buf, 0, buf_length);
      free(buf);
      return (1);
    }
  if ((mode & CREDENTIALS_LOAD_PUBLIC_KEY) != 0
      && _import_public_key(credentials, credentials_dirpath, buf) != 0)
    {
      credentials_clean(credentials);
      memset(buf, 0, buf_length);
      free(buf);
      return (1);
    }
  memset(buf, 0, buf_length);
  free(buf);
  return (0);
}
