# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 11:18:34 by jtu               #+#    #+#              #
#    Updated: 2024/09/24 16:13:50 by jtu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line_bonus.c \
	ft_printf.c \
	ft_put_function.c \
	ft_specifier.c \
	ft_numlen.c \
	ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \

vpath %.c get_next_line ft_printf

CFLAGS = -Wall -Wextra -Werror

OBJS = $(addprefix obj/, $(SRCS:%.c=%.o))

all: ${NAME}

obj/%.o: %.c
	@mkdir -p obj
	@cc $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	@ar rcs $@ $^
	@echo "Libft Compiled!"

clean:
	@rm -rf obj/

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
