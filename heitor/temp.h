
#ifndef TEMP_H
# define TEMP_H

# include <stdio.h>
# include "./libft/incs/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>

# define BUFFER_PATH 4000

typedef struct s_root
{
    char    *line;
    char    **command;
} t_root;

int     array_size(char **array);
void    cd(t_root *root);
void    echo(t_root *root);
void    pwd();
void    env(char **env); //mudar para uma linkes list
void    ft_exit(t_root *root);
void	get_prompt();

#endif
