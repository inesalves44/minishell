

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLXFLAGS	= -lmlx -lXext -lX11 -lm -lbsd

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

all: $(LIBFT)
	cc minishell.c $(LIBFT) -o mini -lreadline 


$(LIBFT):
	@ $(MAKE) -C $(LIBFT_DIR)


fclean: clean
	rm -rf minishell
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
