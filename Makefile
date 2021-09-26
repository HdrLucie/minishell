SRCS =  srcs/main.c

OBJS = ${SRCS:.c=.o}

HEAD = include/minishell.h

INCLUDE =	-Iinclude

NAME = minishell

CC		= clang

CFLAGS	= -Wall -Wextra -Werror

DEBUG_FLAG = -fsanitize=address -g3

.c.o:		${SRCS}
			${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			${MAKE} -C libft
			${CC} ${OBJS} ${CFLAGS} ${INCLUDE} -Llibft -lft  -o ${NAME}

debug:		${SRCS} ${HEAD}
			${CC} ${OBJS} ${CFLAGS} ${DEBUG_FLAG} ${INCLUDE} -Llibft -lft  -o ${NAME}

all: 		${NAME}

clean:
			rm -f srcs/*.o
			${MAKE} clean -C libft

fclean:		clean
			rm -f ${NAME}
			${MAKE} fclean -C libft
			rm -rf minishell.dSYM

re:			fclean all

.PHONY:		all fclean clean re debug
