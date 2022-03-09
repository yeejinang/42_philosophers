# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yang <yang@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 14:10:12 by yang              #+#    #+#              #
#    Updated: 2022/03/09 10:34:07 by yang             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_BOLD		=\e[1m
_R			=\e[0m
_RED		=\e[0;31m
_GRN		=\e[0;32m
_YEL		=\e[0;33m
_BLU		=\e[0;34m
_MAGENTA	=\e[35m
_CYAN		=\e[96m
_WHITE		=\e[97m

NAME	= philo

CC		= gcc

CFLAGS	= -pthread

DIC		= ./

SRCS	= routine.c utils_1.c utils_2.c main.c

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

clean	:
			rm -f *.o

fclean	: clean
			rm -f $(NAME)

re		: fclean all

.PHONY	: all clean fclean re

$(NAME)	: $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@printf "$(_GRN)Compilation completed.\n"
			@printf "$(_BLU)Executable file: $(_BOLD)$(_CYAN)$(NAME)$(_R)\n"

$(DIC)%.o: $(DIC)%.c
			@$(CC) $(CFLAGS) -c $< -o $@
			@printf "$(_GRN)Compiling $(_YEL) $<$(_R)\n"

