NAME = minishell

CC	     = 	gcc
FLAGS 	 =  -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include
CFLAGS   = 	-Wall -Wextra -Werror -g

LIBFT    = 	-L libft -lft
READLINE = -lreadline -L ~/.brew/opt/readline/lib
HEADER = minishell.h

SRCS = minishell.c erroren.c sig.c cmd.c signal.c utils.c parser_special_char.c dollar.c \
       		clean.c envp.c parsing.c cd.c pwd.c env.c export.c echo.c \
       		executor.c listutils.c pipes.c fdes.c envworks.c execve.c freex.c msh_ut.c utils37.c p_utils.c exit.c unset.c utils_export.c
OBJS = $(SRCS:.c=.o)

all : 		$(NAME)

$(NAME) : 	$(OBJS) $(HEADER)
			@make -C libft/
			$(CC) $(CFLAGS) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean :
			@rm -rf $(OBJS)
			@make clean -C libft/
fclean : 	clean
			@rm -rf $(NAME)
			@make fclean -C libft/

re : fclean all

.PHONY: all clean fclean re
