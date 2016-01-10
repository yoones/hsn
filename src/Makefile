##
## This file is part of HSN (Human-Scale Network)
##
## HSN: secure, distributed, SPOF-free network of trust
## Copyright (C) 2016 Younes SERRAJ
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## version 2 as published by the Free Software Foundation.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
## or see <http://www.gnu.org/licenses/>.
##

CC		=	gcc
NAME		=	hsn

SRCS		=	main.c				\
			credentials_clean.c		\
			credentials_init.c		\
			credentials_load.c		\
			hsn_node_clean.c		\
			hsn_node_init.c			\
			hsn_node_load_credentials.c	\
			hsn_node_setup.c		\
			tools/split.c			\
			tools/read_file.c		\
			tools/list.c			\
			tools/find_char.c		\
			tools/xfunctions.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-W -Wall -Wextra
CFLAGS		+=	-g
CFLAGS		+=	-I . -I ../include

LDFLAGS		=	-lssh

RM		=	rm -rf

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean		:
			$(RM) $(NAME)

fclean		:	clean
			$(RM) $(OBJS)

re		:	fclean all

.PHONY		:	all clean fclean re
