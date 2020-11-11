# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 12:40:08 by jlyessa           #+#    #+#              #
#    Updated: 2020/11/09 22:16:13 by tisabel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADERS = includes/minishell.h includes/struct.h

SRCS = srcs/general/main.c srcs/general/get_next_line.c srcs/general/exit.c\
        srcs/general/ft_strcut.c srcs/general/variables.c\
		srcs/parser/copy_array.c srcs/parser/new_arg.c srcs/parser/parce_data.c\
		srcs/cmd/ft_cd.c srcs/cmd/ft_echo.c srcs/cmd/ft_env.c srcs/cmd/ft_exit.c\
		srcs/cmd/ft_export.c srcs/cmd/ft_pwd.c srcs/cmd/ft_unset.c\
		srcs/parser/check_function.c srcs/parser/exec_pipe_semic.c\
		srcs/parser/parce_quotes.c srcs/parser/check_digit.c
OBJ = ${SRCS:.c=.o}

LIBFT_DIR = libft
LIBFT = libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADERS) $(SRCS)
	@gcc $(FLAGS) -Iincludes -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)
	@echo "[minishell] Compile libft"
	@make bonus -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJ) -g -o $(NAME) $(LIBFT_DIR)/$(LIBFT)
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