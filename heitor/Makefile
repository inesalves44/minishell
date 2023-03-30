

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -lreadline -g #-fsanitize=address
MLXFLAGS	= -lmlx -lXext -lX11 -lm -lbsd

SRCS = minishell.c utils.c built_cd.c built_echo.c built_pwd.c built_env.c built_exit.c get_prompt.c \
	   built_export.c envs/env_utils.c envs/init_envs.c envs/get_value.c

all: $(LIBFT)
	cc $(SRCS) $(LIBFT) $(CFLAGS) libft.a -o mini

fclean:
	rm -rf minishell
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
