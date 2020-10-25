# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 12:40:08 by jlyessa           #+#    #+#              #
#    Updated: 2020/10/25 13:35:05 by jlyessa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = includes/

SRCS = srcs/main.c
OBJ = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror -I $(INC)

all: $(NAME)

%.o: %.c
	@gcc $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(OBJ) -o $(NAME)
	@printf "[minishell] Compiled\n"

clean:
	@/bin/rm -f $(OBJ)
	@printf "[minishell] Removed object files\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "[minishell] Removed minishell\n"

re: fclean all

.PHONY: all clean fclean re	