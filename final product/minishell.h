/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:08:03 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/18 18:00:43 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/incs/libft.h"
# include "libft/incs/ft_printf.h"
# include "libft/incs/get_next_line.h"
# include "incs/parse_lexer.h"
# include "incs/lists_structs.h"
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
char		*get_pwd(void);

/*signal*/
void		sig_int(int sig, siginfo_t *info, void *context);

/*prompt*/
void		redisplay_prompt(void);
char		*get_prompt(t_root *root);

/*built in*/
int			built_in_router(t_root *root);
int			cd(t_root *root);
int			echo(t_root *root);
int			pwd(t_root *root);
int			export(t_root *root);
int			unset(t_root *root);
int			env(t_root *root);
int			ft_exit(t_root *root);

/*command*/
char		*get_path(char **envp);
char		*find_path(char *final, char **paths);
int			do_command(t_root *root);

/*error_exit file*/
int			error_process(char *str, t_ast *node, int error);
t_ast		*free_tree(t_ast *node, int a);
void		free_str_split(char **str);
void		close_fd(t_ast *tree, int *pipes);
int			error_syntax(char *str, int error);
t_lexer		*free_lexer(t_lexer *lexer);
void		free_all(t_root *root);

/*pipes*/
int			counting_pipes(t_ast *tree);
int			*creating_pipes(t_ast *tree, int pipes);
int			child_in(t_root *root);
int			child_out(t_root *root); //
int			child_mid(t_root *root);
int			doing_pipes(t_root *root);

/*main*/
int			input_file(t_root *root);
int			output_file(t_root *root);
int			checking_processes(t_root *root);
void		checking_next_node(t_ast **tree);

/*main heitor*/
int			is_built(char **commands);

#endif
