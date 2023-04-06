/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:08:03 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/06 23:37:31 by idias-al         ###   ########.fr       */
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
	int				node;
	int				type;
	int 			*squotes;
	int 			*dquotes;
	char 			**command;
	char 			*file;
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
	t_lexer		*lexer;
	t_ast		*tree;
	char		**env_array;
	t_envlst	*env_lst;
	char		*user;
	char		*prompt;
	char		*line;
	int			in;
	int			out;
	int			*pipes;
	int			status;
	int			num_pipes;
}	t_root;


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


/*parsing*/
int		get_file(t_lexer **lexer, t_ast *node);
char	**treat_string(t_lexer **lexer, t_ast **aux, t_ast **tree);
t_ast	*create_treenode(t_lexer **lexer, t_ast **aux, int check);
void	print_tree(t_ast *node, int i);
int		parsing_str(t_lexer **lexer, t_ast **tree);

/*command*/
char	*get_path(char **envp);
char	*find_path(char *final, char **paths);
int		do_command(t_root *root);

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
int	child_in(t_root *root);//t_ast *tree, int in, int out, int *pipes, char *envp[]);
int	child_out(t_root *root); //t_ast *tree, int in, int out, int *pipes, char *envp[]);
int	child_mid(t_root *root);
int	doing_pipes(t_root *root);

/*lexical*/
int	lexical_annalysis(t_lexer **node, char *str);

/*main*/
int		input_file(t_root *root);
int		output_file(t_root *root);
int		checking_processes(t_root *root);
void	checking_next_node(t_ast **tree);

/*main heitor*/
int		is_built(char **commands);

#endif
