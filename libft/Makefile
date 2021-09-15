# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 20:33:41 by mpochard          #+#    #+#              #
#    Updated: 2021/03/13 13:59:51 by mpochard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
		ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isalnum.c \
		ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
		ft_atoi.c  ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_swap.c \
		ft_isin.c ft_absitoa.c ft_putchar.c

OBJS = ${SRC:.c=.o}

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

RM = rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all  : ${NAME}

${NAME}: 	${OBJS}
			ar rcs ${NAME} ${OBJS}


clean :
		${RM} ${OBJS}

fclean : 	clean
			${RM} ${NAME}

re : 		fclean all


.PHONY : all clean fclean re 
