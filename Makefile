SRCS =  srcs/main.c 					\
		srcs/cmd/init_cmd.c 			\
		srcs/parser/parse_path.c 		\
		srcs/parser/lst_cmd_utils.c 	\
		srcs/parser/lexer.c				\
		srcs/parser/parser.c				\
		srcs/parser/ft_split_quote.c	\
		srcs/parser/split_quote_utils.c \
		srcs/builtins/env.c				\
		srcs/builtins/lst_utils.c		\
		srcs/builtins/pwd.c 			\
		srcs/builtins/recover_cmd.c		\
		srcs/builtins/exit.c			\
		srcs/builtins/export.c			\
		srcs/builtins/unset.c			\
		srcs/builtins/export_utils.c	\
		srcs/builtins/print_utils.c		\


OBJS = ${SRCS:.c=.o}

HEAD = include/minishell.h

INCLUDE =	-Iinclude

NAME = minishell

CC		= clang

CFLAGS	= -Wall -Wextra -Werror

DEBUG_FLAG =  -g3

.c.o:		${SRCS}
			${CC} ${CFLAGS} ${DEBUG_FLAG} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			make -C libft
			${CC} ${OBJS} ${CFLAGS} ${INCLUDE} -Llibft -lft -lreadline -o ${NAME}
			@echo "\033[33;31mCOMPILED\t\t\tCONGRATS\033[0m"


debug:		${SRCS} ${HEAD}
			@${CC} ${OBJS} ${CFLAGS} ${DEBUG_FLAG} ${INCLUDE} -Llibft -lft -lreadline -o ${NAME}

all: 		${NAME}

clean:
			@rm -f ${OBJS}
			@make clean -C libft
			@echo "\033[33;34mCLEAN !\t\t\t\tBUT YOU CAN DO BETTER\033[0m"

fclean:		clean
			rm -f ${NAME}
			@make fclean -C libft
			rm -rf minishell.dSYM
			@echo "\033[33;32mALL CLEAN !\t\t\tYOU'RE VERY PROPER\033[0m"

re:			fclean all
			@echo "\033[33;36mRECOMPILED !\t\t\tIT'S WORK NOW ?\033[0m"

.PHONY:		all fclean clean re debug
