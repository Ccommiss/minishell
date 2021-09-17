SOURCES =	main.c\

SPATH = srcs/

SRCS  += $(addprefix $(SPATH), $(SOURCES))

OBJS	= 	${SRCS:.c=.o}

CC = gcc 

CFLAGS = -Wall -Werror -Wextra -fsanitize=address

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

