

CC			= cc
CFLAGS		= -lreadline -g #-fsanitize=address
LIBFT = libft.a
OBJS = main.o parsing.o command.o error_exit.o pipes.o lexical.o
NAME = minishell

all: $(OBJS)
	$(MAKE) --no-print-directory -C libft
	cp libft/$(LIBFT) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	$(MAKE) clean --no-print-directory -C libft
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean --no-print-directory -C libft
	rm -rf $(NAME)

re: fclean all
