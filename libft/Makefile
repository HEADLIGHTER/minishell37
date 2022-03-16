NAME 	= libft.a

SRCS 	= ft_strmapi.c ft_split.c ft_strtrim.c ft_itoa.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_putnbr_fd.c \
			ft_strjoin.c ft_substr.c ft_strdup.c ft_calloc.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
			ft_isinset.c find_char.c ft_lstrm.c

OBJS 	= ${SRCS:.c=.o}

CFLAGS 	= -Wall -Wextra -Werror

RM 		= rm -f

AR		= ar rcs

CC		= gcc

HEADER	= -I libft.h
.c.o:
		${CC} ${CFLAGS} -c ${HEADER} $< -o ${<:.c=.o}

all: 	${NAME}

${NAME}:	${OBJS}
		${AR} ${NAME} $?
clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re