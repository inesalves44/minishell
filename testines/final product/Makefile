LIBFT = libft.a
OBJS = main.o \
	   envs/init_envs.o envs/env_utils.o envs/get_value.o get_prompt.o \
	   built-in/built_cd.o built-in/built_echo.o  built-in/built_pwd.o \
	   built-in/built_export.o built-in/built_unset.o command.o error_exit.o \
	   lexical.o simple.o parsing.o pipes.o  
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) --no-print-directory -C libft
	cp libft/$(LIBFT) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	$(MAKE) clean --no-print-directory -C libft
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean --no-print-directory -C libft
	rm -rf $(NAME) $(LIBFT)

re: fclean all
