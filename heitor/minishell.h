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

typedef enum types
{
    pipem = 1,
    red_in = 2,
    red_out = 3,
    command = 4,
    file = 5,
	here_doc = 6,
	app_out = 7,
	s_quotes = 87,
	d_quotes = 82,
}	check;

typedef struct ast_tree
{
	int	node;
	int	type;
	int quotes;
	char **command;
	char *file;
	struct ast_tree *left;
	struct ast_tree *rigth;
	struct ast_tree *prev;
}	t_ast;

typedef struct	lexer_list
{
	char				*str;
	int					number;
	int					type;
	struct	lexer_list	*next;
	struct	lexer_list	*prev;
}	t_lexer;

typedef	struct s_root
{
	t_lexer	*lexer;
	t_ast		*tree;
	char		**env_array;
	t_envlst	*env_lst;
	char		*user;
	char		*prompt;
	char		*line;
	int		in;
	int		out;
	int		*pipes;
	int		status;
	int		num_pipes;
	char	**str;
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
char		*get_value_from_str(char *env);
char		*get_key_from_str(char *env);
void		free_array(char **array);
void		free_env_node(t_envlst *node);

/*utils*/
char		*transform(char cwd[]);
int			is_equal(char *command, char *key);
char		*get_pwd();

/*signal*/
void		sig_int(int sig, siginfo_t *info, void *context);

/*prompt*/
void		redisplay_prompt();
char		*get_prompt(t_root *root);

/*built in*/
int		built_in_router(t_root *root);
int		cd(t_root *root);
int		echo(t_root *root);
int		pwd();
int		export(t_root *root);
int		unset(t_root *root);


/*parsing*/
int		get_file(t_lexer **lexer, t_ast *node);
char	**treat_string(t_lexer **lexer, t_ast *aux);
t_ast	*create_treenode(t_lexer **lexer, t_ast *aux, int check);
void	print_tree(t_ast *node, int i);
int		parsing_str(t_lexer **lexer, t_ast **tree);

/*command*/
char	*get_path(char **envp);
char	*find_path(char *final, char **paths);
int		do_command(t_ast *tree, int in, int out, char *envp[]);

/*error_exit file*/
int		error_process(char *str, t_ast *node, int error);
void	free_tree(t_ast **node, int a);
void	free_str_split(char **str);
void	close_fd(t_ast *tree, int *pipes);
int		error_syntax(char *str, int error);
void	free_lexer(t_lexer **lexer);

/*pipes*/
int	counting_pipes(t_ast *tree);
int	*creating_pipes(t_ast *tree, int pipes);
int	child_in(t_ast *tree, int in, int out, int *pipes, char *envp[]);
int	child_out(t_ast *tree, int in, int out, int *pipes, char *envp[]);
int	child_mid(t_ast *tree, int in, int out, int *pipes, char *envp[]);
int	doing_pipes(t_ast **tree, int in, int out, char *envp[]);

/*lexical*/
int	lexical_annalysis(t_lexer **node, char *str);

/*main*/
int	input_file(t_ast *node, int *fd);
int	output_file(t_ast *node, int *fd);

#endif
