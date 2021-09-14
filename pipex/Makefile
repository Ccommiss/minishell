# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 14:50:16 by ccommiss          #+#    #+#              #
#    Updated: 2021/07/22 16:14:20 by ccommiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex


SRC_FOLD = ./srcs/

SRCS = $(SRC_FOLD)handle_args_and_cmds.c \
	$(SRC_FOLD)pipe_communicating.c \
	$(SRC_FOLD)utils.c \
	$(SRC_FOLD)utils/ft_strconcat.c \
	$(SRC_FOLD)utils/ft_split.c \
	$(SRC_FOLD)utils/ft_memdel.c \
	$(SRC_FOLD)utils/ft_strlen.c \
	$(SRC_FOLD)utils/ft_strdup.c \
	$(SRC_FOLD)utils/ft_putendl_fd.c \
	$(SRC_FOLD)utils/ft_free_double_tab.c \
	$(SRC_FOLD)utils/ft_strncmp.c \
	$(SRC_FOLD)utils/ft_memcpy.c \
	$(SRC_FOLD)utils/malloc_char_pointer.c \

SRCS_BONUS = $(SRC_FOLD)handle_args_and_cmds.c \
	$(SRC_FOLD)pipe_communicating.c \
	$(SRC_FOLD)utils_bonus.c \
	$(SRC_FOLD)utils/ft_strconcat.c \
	$(SRC_FOLD)utils/ft_split.c \
	$(SRC_FOLD)utils/ft_memdel.c \
	$(SRC_FOLD)utils/ft_strlen.c \
	$(SRC_FOLD)utils/ft_strdup.c \
	$(SRC_FOLD)utils/ft_putendl_fd.c \
	$(SRC_FOLD)utils/ft_free_double_tab.c \
	$(SRC_FOLD)utils/ft_strncmp.c \
	$(SRC_FOLD)utils/ft_memcpy.c \
	$(SRC_FOLD)utils/malloc_char_pointer.c \


INCLUDES = /includes/
FLAGS = -I.$(INCLUDES) -Wall -Werror -Wextra
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
CC = @clang -g $(FLAGS)


all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo ">> Classic version of pipex. Only one pipe handled.\nFor more: make bonus."

bonus : $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) -o $(NAME)
	@echo ">> Multiple pipes handled. Have fun !"

clean :
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	@rm $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re

