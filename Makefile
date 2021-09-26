SRCS =  srcs/main.c

OBJS = ${SRCS:.c=.o}

HEAD = include/minishell.h

INCLUDE =	-Iinclude

NAME = minishell

CC		= clang

CFLAGS	= -Wall -Wextra -Werror

DEBUG_FLAG = -fsanitize=address -g3

.c.o:		${SRCS}
			@${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			@make -C libft
			@${CC} ${OBJS} ${CFLAGS} ${INCLUDE} -Llibft -lft -lreadline -o ${NAME}
			@echo "\033[33;31mCOMPILED\t\t\tCONGRATS"


debug:		${SRCS} ${HEAD}
			@${CC} ${OBJS} ${CFLAGS} ${DEBUG_FLAG} ${INCLUDE} -Llibft -lft -lreadline -o ${NAME}

all: 		${NAME}

clean:
			@rm -f srcs/*.o
			@make clean -C libft
			@echo "\033[33;34mCLEAN !\t\t\t\tBUT YOU CAN DO BETTER"

fclean:		clean
			rm -f ${NAME}
			@make fclean -C libft
			rm -rf minishell.dSYM
			@echo "\033[33;32mALL CLEAN !\t\t\tYOU'RE VERY PROPER"

re:			fclean all
			@echo "\033[33;36mRECOMPILED !\t\t\tIT'S WORK NOW ?"

.PHONY:		all fclean clean re debug
