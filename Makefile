
LEX_PATH = a_lexer
PAR_PATH = b_parser
EXEC_PATH = c_exec
ENV_PATH = d_env
BUILT_PATH = e_builtin
REDIR_PATH = f_redirection
PIPE_PATH = g_pipe

SOURCES =	main.c\
			$(LEX_PATH)/tokenizer2.c \
			$(LEX_PATH)/init_token.c \
			$(LEX_PATH)/expand.c \
			$(LEX_PATH)/lex_error_detector.c \
			$(LEX_PATH)/quotes.c \
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
			$(ENV_PATH)/list_to_tab.c \
			${BUILT_PATH}/cd.c\
			${BUILT_PATH}/echo.c\
			${BUILT_PATH}/exit.c\
			${REDIR_PATH}/is_redir.c\
			${REDIR_PATH}/redir_out.c\
			${REDIR_PATH}/redir_in.c\
			${REDIR_PATH}/here_doc.c\
			${REDIR_PATH}/util_redir.c\
			${REDIR_PATH}/fill_thefd.c\
			${EXEC_PATH}/cmd_to_exec.c\
			${PIPE_PATH}/do_pipe.c\
			${PIPE_PATH}/first_pid.c\
			${PIPE_PATH}/other_pid.c\
			${PIPE_PATH}/last_pid.c\
			${PIPE_PATH}/util_pipe.c\
			${EXEC_PATH}/signals.c \
			${EXEC_PATH}/set_status.c \
			utils.c






SPATH = srcs/
INCLUDES = /includes/

SRCS  += $(addprefix $(SPATH), $(SOURCES))

OBJS	= 	${SRCS:.c=.o}

CC = gcc

#CFLAGS = -g -I.$(INCLUDES) -Wall -Werror -Wextra# -fsanitize=address
CFLAGS = -g -I.$(INCLUDES) -I/usr/local/opt/readline/include  -Wall -Werror -Wextra -fsanitize=address

RM = rm -f

NAME = minishell

%.o: %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		${MAKE} -C libft/
		${CC} ${CFLAGS} ${OBJS} -lreadline -L/usr/local/opt/readline/lib libft/libft.a -o ${NAME}
	#	${CC} ${CFLAGS} ${OBJS} -lreadline libft/libft.a -o ${NAME}
all: ${NAME}

clean :
		${RM} ${OBJS}
		${MAKE} clean -C libft/
fclean : clean
		${RM} ${NAME}
		${MAKE} fclean -C libft/

re:	 fclean all

.PHONY: all clean fclean re
