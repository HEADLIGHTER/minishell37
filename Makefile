NAME = minishell

CC = gcc
CC_F = -Wall -Wextra

LIBFT = ./libft/
READLINE = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
HEADER = minishell.h

SRCS = main.c cmd.c signal.c utils.c parser_special_char.c dollar.c clean.c envp.c parsing.c
OBJS = $(SRCS:.c=.o)


all : 		$(NAME)

%.o: %.c	$(SRCS)
			@$(CC) $(CC_F) -I$(HEADER) -I$(LIBFT)libft.h -c $< -o $@

$(NAME) : 	$(OBJS) $(HEADER)
			@make -C $(LIBFT)
			@$(CC) $(READLINE) $(LIBFT)libft.a $(CC_F) $(OBJS) -o $(NAME)

clean :
			@rm -rf $(OBJS)
			@make clean -C $(LIBFT)
fclean : 	clean
			@rm -rf $(NAME)
			@make fclean -C $(LIBFT)
re : fclean all

.PHONY: all clean fclean re