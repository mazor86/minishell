# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 12:40:08 by jlyessa           #+#    #+#              #
#    Updated: 2020/10/25 23:24:44 by tisabel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = includes/

SRCS = srcs/main.c
OBJ = ${SRCS:.c=.o}

MY_LIBFT = libft

FLAGS = -Wall -Wextra -Werror -I $(INC)

all: $(NAME)

%.o: %.c
	@gcc $(FLAGS) $< -o $@

$(NAME): $(OBJ) $(MY_LIBFT)
	@echo "compile libft"
	@make bonus -C $(MY_LIBFT)
	@gcc $(FLAGS) $(OBJ) -o $(NAME)
	@echo "[minishell] Compiled\n"

clean:
	@make clean -C $(MY_LIBFT)
	@/bin/rm -f $(OBJ)
	@echo "[minishell] Removed object files\n"

fclean: clean
	@make fclean -C $(MY_LIBFT)
	@/bin/rm -f $(NAME)
	@echo "[minishell] Removed minishell\n"

re: fclean all

.PHONY: all clean fclean re	