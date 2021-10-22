
LEX_PATH = a_lexer
PAR_PATH = b_parser
EXEC_PATH = c_exec
ENV_PATH = d_env
BUILT_PATH = e_builtin
REDIR_PATH = f_redirection

SOURCES =	main.c\
			$(LEX_PATH)/tokenizer2.c \
			$(LEX_PATH)/init_token.c \
			$(LEX_PATH)/expand.c \
			$(LEX_PATH)/debug_tokens.c \
			$(LEX_PATH)/context.c \
			$(PAR_PATH)/find_path.c \
			$(PAR_PATH)/redirect.c \
			$(PAR_PATH)/token_to_cmds.c \
			$(PAR_PATH)/debug_cmds.c \
			$(ENV_PATH)/get_the_env.c \
			$(ENV_PATH)/the_list.c \
			$(ENV_PATH)/unset.c \
			$(ENV_PATH)/export_the_var.c \
			${BUILT_PATH}/cd.c\
			${BUILT_PATH}/echo.c\
			${REDIR_PATH}/is_redir.c\
			${REDIR_PATH}/redir_out.c\
			${REDIR_PATH}/redir_in.c\
			${REDIR_PATH}/here_doc.c\
			${EXEC_PATH}/cmd_to_exec.c\





SPATH = srcs/
INCLUDES = /includes/

SRCS  += $(addprefix $(SPATH), $(SOURCES))

OBJS	= 	${SRCS:.c=.o}

CC = clang

CFLAGS = -g -I.$(INCLUDES) -Wall -Werror -Wextra -fsanitize=address -fno-omit-frame-pointer

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
