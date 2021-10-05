SRCS  = ft_realloc.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BNS		= ft_strslen.c ft_abs.c ft_split_str.c ft_strtrim_path.c ft_strjoin_size.c ft_itoa_unsigned.c ft_memalloc.c ft_putendl.c  ft_strcat.c   ft_strcpy.c   ft_striter.c  ft_strncat.c  ft_strstr.c ft_memdel.c   ft_putnbr.c   ft_strclr.c   ft_strdel.c   ft_striteri.c ft_strnequ.c ft_putchar.c  ft_putstr.c   ft_strcmp.c   ft_strequ.c   ft_strmap.c   ft_strnew.c

OBJS = ${SRCS:.c=.o}

OBJS2 = ${BNS:.c=.o}

DEPS = -I .

NAME = libft.a

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

.c.o:		${SRCS} ${BNS}
			@${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${OBJS2}
			@ar rc ${NAME} ${OBJS} ${OBJS2}

all: 		${NAME}

clean:
			@rm -f ${OBJS}
			@rm -f ${OBJS2}

fclean:		clean
			@rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
