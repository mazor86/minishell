# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlyessa <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 12:40:08 by jlyessa           #+#    #+#              #
#    Updated: 2020/10/26 13:09:02 by jlyessa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADERS = includes/minishell.h

SRCS = srcs/main.c
OBJ = ${SRCS:.c=.o}

MY_LIBFT = libft

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADERS) $(SRCS)
	@gcc $(FLAGS) -с $< -o $@

$(NAME): $(OBJ) $(MY_LIBFT)
	@echo "[minishell] Compile libft"
	@make bonus -C $(MY_LIBFT)
	@gcc $(FLAGS) $(OBJ) -o $(NAME)
	@echo "[minishell] Compiled"

clean:
	@make clean -C $(MY_LIBFT)
	@/bin/rm -f $(OBJ)
	@echo "[minishell] Removed object files"

fclean: clean
	@make fclean -C $(MY_LIBFT)
	@/bin/rm -f $(NAME)
	@echo "[minishell] Removed minishell"

re: fclean all

.PHONY: all clean fclean re	