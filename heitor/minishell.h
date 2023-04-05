/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:08:03 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/03 08:20:24 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/incs/libft.h"
# include "libft/incs/ft_printf.h"
# include "libft/incs/get_next_line.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

# define TRUE 1
# define FALSE 0
# define BUFFER_PATH 100

typedef enum types
{
    pipem,
    red_in,
    red_out,
    command,
    file,
} check;

typedef enum io
{
    STDIN,
    STDOUT,
    STDERR,
} io;

typedef	struct	s_envlst
{
	char			*key;
	char			*value;
	struct s_envlst	*next;
} t_envlst;

typedef struct ast_tree
{
	int	node;
	int type;
	char **command;
	char *file;
	struct ast_tree *left;
	struct ast_tree *rigth;
	struct ast_tree *prev;
} t_ast;

typedef	struct s_root
{
	t_ast		*tree;
	char		**env_array;
	t_envlst	*env_lst;
	char		*user;
	char		*prompt;
	char		*line;
	char		**str;
	char		**command;
} t_root;

/* env funcs*/

void		init_envp(t_root *root, char **envp);
void		print_envlsts(t_root *root);
void		ft_lstadd_back_env(t_envlst **envs, t_envlst *new);
t_envlst	*ft_lstlast_envlst(t_envlst *envs);
t_envlst	*ft_lstnew_env(char *key, char *value);
void		free_envp_lst(t_root *root);
void		free_envp_array(t_root *root);
void		refresh_env_array(t_root *root);
int			get_array_size(char **array);
int			get_lst_size(t_envlst *lst);
char		*ft_strjoin_gnl(char *s1, char *s2);
int			print_env_value(t_root *root, char *key);
char		*get_env_value(t_root *root, char *key);
int			change_value(t_root *root, char *key, char *new_value);
char		*get_prompt(t_root *root);
char		*get_value_from_str(char *env);
char		*get_key_from_str(char *env);
void		free_array(char **array);

/*built in*/
int		built_in_router(t_root *root);
void	cd(t_root *root);
void    echo(t_root *root);
void	pwd(t_root *root);
void	export(t_root *root);
void	unset(t_root *root);


#endif
