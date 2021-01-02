# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
<<<<<<< HEAD
#    Created: 2020/12/03 21:04:29 by jlyessa           #+#    #+#              #
#    Updated: 2020/12/29 12:37:46 by jlyessa          ###   ########.fr        #
=======
#    Created: 2020/10/25 12:40:08 by jlyessa           #+#    #+#              #
#    Updated: 2020/12/08 17:23:14 by tisabel          ###   ########.fr        #
>>>>>>> tisabel
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g
LIBFT = libft.a

<<<<<<< HEAD
SRCS = srcs/main.c \
		srcs/env/parser_env.c \
		srcs/env/util_env.c \
		srcs/parser/parser_string.c \
		srcs/parser/parser_shielding.c \
		srcs/parser/parser_variables.c \
		srcs/parser/parser_quotes.c \
		srcs/parser/parser_cmd.c \
		srcs/parser/parser_path.c \
		srcs/parser/parser_errors.c \
		srcs/parser/utils.c \
		srcs/parser/convert.c \
		srcs/init/init.c \
		srcs/clear/clear.c \
		srcs/clear/error.c \
		srcs/cmd/ft_echo.c \
		srcs/cmd/ft_pwd.c \
		srcs/cmd/ft_export.c \
		srcs/cmd/ft_env.c \
		srcs/cmd/ft_unset.c \
		srcs/cmd/ft_cd.c \
		srcs/cmd/ft_exit.c
OBJ = $(SRCS:.c=.o)
=======
SRCS = srcs/main.c srcs/general/get_next_line.c srcs/general/exit.c\
        srcs/general/ft_strcut.c srcs/general/variables.c srcs/general/conv_envp.c\
		srcs/parser/copy_array.c srcs/parser/new_arg.c srcs/parser/parce_data.c\
		srcs/cmd/ft_cd.c srcs/cmd/ft_echo.c srcs/cmd/ft_env.c srcs/cmd/ft_exit.c\
		srcs/cmd/ft_export.c srcs/cmd/ft_pwd.c srcs/cmd/ft_unset.c\
		srcs/parser/check_function.c srcs/parser/exec_pipe_semic.c\
		srcs/parser/parce_quotes.c srcs/parser/check_digit.c 
OBJ = ${SRCS:.c=.o}
>>>>>>> tisabel

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