# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 12:40:08 by jlyessa           #+#    #+#              #
#    Updated: 2020/10/27 14:00:51 by jlyessa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADERS = includes/minishell.h

SRCS = srcs/main.c srcs/get_next_line.c
OBJ = ${SRCS:.c=.o}

LIBFT_DIR = libft
LIBFT = libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADERS) $(SRCS)
	@gcc $(FLAGS) -с $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)
	@echo "[minishell] Compile libft"
	@make bonus -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)
	@echo "[minishell] Compiled"

clean:
	@make clean -C $(LIBFT_DIR)
	@/bin/rm -f $(OBJ)
	@echo "[minishell] Removed object files"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@/bin/rm -f $(NAME)
	@echo "[minishell] Removed minishell"

re: fclean all

.PHONY: all clean fclean re	