
#ifndef TEMP_H
# define TEMP_H

# include <stdio.h>
# include "./libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>

# define BUFFER_PATH 4000

typedef struct s_env
{
    char    		*key;
    char            *value;
    struct s_env	*next;
} t_env;

typedef struct s_root
{
    char    *line;
    char    *prompt;
    char    **command;
	char	**path;
    t_env   *envs;
} t_root;


int     array_size(char **array);
void    cd(t_root *root);
void    echo(t_root *root);
void    pwd();
void	export(t_root *root);
void    env(t_root *root);
void    ft_exit(t_root *root);
void	get_prompt(t_root *root);
char    *get_pwd();


t_env	*ft_lstnew_env(char *key, char *value);
t_env	*ft_lstlast_env(t_env *envs);
void	ft_lstadd_back_env(t_env **envs, t_env *new);
void	init_envs(t_root *root, char **envp);
void	print_envs(t_root *root);


int	ft_keylen(char *env);
char	*extract_key(char *env);
char	*extract_value(char *env);
char    *get_env_value(t_root *root, char *key);
int	    change_value(t_root *root, char *key, char *new_value);

#endif
