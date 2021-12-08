
LEX_PATH = a_lexer
PAR_PATH = b_parser
EXEC_PATH = c_exec
ENV_PATH = d_env
BUILT_PATH = ${EXEC_PATH}/builtins_functions
REDIR_PATH = ${EXEC_PATH}/redirections
PIPE_PATH = ${EXEC_PATH}/pipes_management
UTILS_PATH = e_utils

SOURCES =	main.c\
			$(LEX_PATH)/tokenizer.c \
			$(LEX_PATH)/init_funcs.c \
			$(LEX_PATH)/expand.c \
			$(LEX_PATH)/valid_expand_char_tab.c \
			$(LEX_PATH)/lex_error_detector.c \
			$(LEX_PATH)/quotes.c \
			$(LEX_PATH)/debug_tokens.c \
			$(LEX_PATH)/create_tokens_funcs.c \
			$(LEX_PATH)/context.c \
			$(PAR_PATH)/find_path.c \
			$(PAR_PATH)/redirect.c \
			$(PAR_PATH)/token_to_cmds.c \
			$(PAR_PATH)/debug_cmds.c \
			$(PAR_PATH)/parse_error_detector.c \
			$(PAR_PATH)/command_and_suffix.c \
			$(PAR_PATH)/init_cmd.c \
			$(ENV_PATH)/get_the_env.c \
			$(ENV_PATH)/the_list.c \
			$(ENV_PATH)/unset.c \
			$(ENV_PATH)/export_the_var.c \
			$(ENV_PATH)/list_to_tab.c\
			$(ENV_PATH)/util_print_exp.c\
			$(ENV_PATH)/parse_exp.c \
			$(ENV_PATH)/print_exp.c \
			$(ENV_PATH)/util_unset.c \
			$(ENV_PATH)/util_env.c \
			${BUILT_PATH}/cd.c\
			${BUILT_PATH}/echo.c\
			${BUILT_PATH}/exit.c\
			${BUILT_PATH}/exit_pipe.c\
			${BUILT_PATH}/cd_utils.c\
			${BUILT_PATH}/pwd.c\
			${REDIR_PATH}/is_redir.c\
			${REDIR_PATH}/redir_out.c\
			${REDIR_PATH}/redir_in.c\
			${REDIR_PATH}/here_doc.c\
			${REDIR_PATH}/util_redir.c\
			${REDIR_PATH}/util_error.c\
			${REDIR_PATH}/util_fillfd.c\
			${REDIR_PATH}/fill_thefd.c\
			${EXEC_PATH}/cmd_to_exec.c\
			${PIPE_PATH}/do_pipe.c\
			${PIPE_PATH}/first_pid.c\
			${PIPE_PATH}/other_pid.c\
			${PIPE_PATH}/last_pid.c\
			${PIPE_PATH}/util_pipe.c\
			${EXEC_PATH}/signals.c \
			${EXEC_PATH}/set_status.c \
			$(UTILS_PATH)/cleanup.c \
			$(UTILS_PATH)/ft_print_errors.c \
			$(UTILS_PATH)/ft_exit_program.c \
			$(UTILS_PATH)/unclosed_quotes_management.c







SPATH = srcs/
OPATH = objs/
INCLUDES = /includes/

SRCS  += $(addprefix $(SPATH), $(SOURCES))


OBJS	= 	${SRCS:.c=.o}
CC = gcc

CFLAGS = -g -I.$(INCLUDES) -I/usr/local/opt/readline/include  -Wall -Werror -Wextra 

RM = rm -f

NAME = minishell

$(OPATH)%.o: %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		${MAKE} -C libft/
		${CC} ${CFLAGS} ${OBJS} -lreadline -L/usr/local/opt/readline/lib libft/libft.a -o ${NAME}
all: ${NAME}

clean :
		${RM} ${OBJS}
		${MAKE} clean -C libft/
fclean : clean
		${RM} ${NAME}
		${MAKE} fclean -C libft/

re:	 fclean all

.PHONY: all clean fclean re
