SOURCES = get_next_line.c\
		  main.c\
SPATH = srcs/

SOURCES  += $(addprefix $(SPATH), $(SOURCES))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I ./include/ 

RM = rm -f

NAME = minishell 

#-fds=yes 
%.o: %.c 
	${CC} ${CFLAGS} -C $< -o ${<:.c=.o}
${NAME}: ${OBJS}
		${MAKE} -c libft/ 
		${CC} ${OBJS} libft/libft.a -o ${NAME}
all: ${NAME}

clean : 
		${RM} ${OBJS}
		${MAKE} clean -C libft/
fclean : clean
		${RM} ${NAME}
		${MAKE} fclean -C libft/
re:	 fclean all

.PHONY: all clean fclean re

