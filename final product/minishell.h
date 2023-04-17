/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:08:03 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/17 15:15:14 by hmaciel-         ###   ########.fr       */
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
# include "incs/envs_built.h"
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

/*utils*/
char		*transform(char cwd[]);
int			is_equal(char *command, char *key);
char		*get_pwd(void);

/*signal*/
void		sig_int(int sig, siginfo_t *info, void *context);

/*prompt*/
void		redisplay_prompt(void);
char		*get_prompt(t_root *root);

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

#endif
