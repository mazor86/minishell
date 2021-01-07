# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/03 21:04:29 by jlyessa           #+#    #+#              #
#    Updated: 2021/01/07 22:46:55 by tisabel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g
LIBFT = libft.a

SRCS = srcs/main.c \
		srcs/parser/utils.c \
		srcs/parser/parser_variables.c \
		srcs/parser/parser_string.c \
		srcs/parser/parser_shielding.c \
		srcs/parser/parser_quotes.c \
		srcs/parser/parser_path.c \
		srcs/parser/parser_errors.c \
		srcs/parser/parser_cmd.c \
		srcs/parser/parser_begin.c \
		srcs/parser/convert.c \
		srcs/init/init.c \
		srcs/general/variables.c \
		srcs/general/conv_envp.c \
		srcs/env/env_utils.c \
		srcs/cmd_utils/cmd_last.c \
		srcs/cmd_utils/add_back_cmd.c \
		srcs/cmd/ft_unset.c \
		srcs/cmd/ft_pwd.c \
		srcs/cmd/ft_export.c \
		srcs/cmd/ft_exit.c \
		srcs/cmd/ft_env.c \
		srcs/cmd/ft_echo.c \
		srcs/cmd/ft_cd.c \
		srcs/clear/clear.c \
		srcs/clear/error.c \

OBJ = $(SRCS:.c=.o)

HEADER = includes/minishell.h libft/libft.h

%.o: %.c
	@gcc $(FLAGS) -c -o $@ $^

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	mv libft/$(LIBFT) .
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

bonus: all

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

norminette:
	@norminette $(SRCS) $(HEADER) libft/*.c

.PHONY: all clean fclean bonus re