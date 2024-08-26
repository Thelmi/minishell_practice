# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 14:53:08 by krazikho          #+#    #+#              #
#    Updated: 2024/08/21 18:18:18 by mrhelmy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell #changed name of the program

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline


NAME_SRCS = main.c utils.c execute_command.c execute_builtin.c storing_env.c free.c ft_split.c ./builtins/unset.c ./builtins/export_no_args.c ./builtins/export_with_args.c ./builtins/pwd.c ./builtins/env.c

NAME_OBJS = $(NAME_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(NAME_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(NAME_OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(NAME_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re #Do we need it ?
