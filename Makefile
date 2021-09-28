

LEX_PATH = a_lexer
PAR_PATH = b_parser
EXEC_PATH = c_exec
ENV_PATH = d_env


SOURCES =	main.c\
			$(LEX_PATH)/tokenizer2.c \
			$(LEX_PATH)/init_token.c \
			$(ENV_PATH)/get_the_env.c



SPATH = srcs/

SRCS  += $(addprefix $(SPATH), $(SOURCES))

OBJS	= 	${SRCS:.c=.o}

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -fsanitize=address

RM = rm -f

NAME = minishell

%.o: %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		${MAKE} -C libft/
		${CC} ${CFLAGS} ${OBJS} -lreadline libft/libft.a -o ${NAME}
all: ${NAME}

clean :
		${RM} ${OBJS}
		${MAKE} clean -C libft/
fclean : clean
		${RM} ${NAME}
		${MAKE} fclean -C libft/

re:	 fclean all

.PHONY: all clean fclean re

