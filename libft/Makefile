# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/08 10:08:33 by tisabel           #+#    #+#              #
#    Updated: 2020/10/16 21:21:21 by tisabel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_isascii.c ft_memcmp.c ft_strdup.c \
ft_strnstr.c ft_bzero.c ft_isdigit.c ft_memcpy.c\
ft_strlcat.c ft_strrchr.c ft_calloc.c ft_isprint.c\
ft_memmove.c ft_strlcpy.c ft_tolower.c ft_isalnum.c\
ft_memccpy.c ft_memset.c ft_strlen.c ft_toupper.c\
ft_isalpha.c ft_memchr.c ft_strchr.c ft_strncmp.c\
ft_itoa.c ft_putendl_fd.c ft_putstr_fd.c ft_strjoin.c\
ft_strtrim.c ft_putchar_fd.c ft_putnbr_fd.c ft_split.c\
ft_strmapi.c ft_substr.c

OBJECTS = $(SRCS:.c=.o)

SRCS_BONUS = ft_lstadd_back.c ft_lstdelone.c ft_lstmap.c\
ft_lstadd_front.c ft_lstiter.c ft_lstnew.c\
ft_lstclear.c ft_lstlast.c ft_lstsize.c ft_min_bonus.c\
ft_max_bonus.c ft_strstr_bonus.c

OBJECTS_BONUS = $(SRCS_BONUS:.c=.o)

HEADER = libft.h

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	@echo "compile main part"
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

bonus: $(OBJECTS) $(OBJECTS_BONUS)
	@echo "compile bonus part"
	@ar rc $(NAME) $(OBJECTS) $(OBJECTS_BONUS)
	@ranlib $(NAME)

%.o: %.c $(HEADER)
	@gcc -Wall -Werror -Wextra -c $< -o $@

clean:
	@echo "clean .o files"
	@/bin/rm -f *.o

fclean: clean
	@echo "clean library file"
	@/bin/rm -f $(NAME)

re: fclean all
	@echo "remaking library"
