
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

typedef struct s_env
{
    char    		*var;
    struct s_env	*next;
} t_env;

int     array_size(char **array);
void    cd(t_root *root);
void    echo(t_root *root);
void    pwd();
void	export(t_root *root, t_env **envs);
void    env(t_env *env);
void    ft_exit(t_root *root);
void	get_prompt();


t_env	*ft_lstnew_env(char *var);
t_env	*ft_lstlast_env(t_env *envs);
void	ft_lstadd_back_env(t_env **envs, t_env *new);
void	init_envs(t_env **envs, char **envp);
void	print_envs(t_env *envs);

#endif
