/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:47:25 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/02 19:48:34 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_REDIRECTS_H
# define EXEC_REDIRECTS_H

# include "../minishell.h"

/*==================redirects============================*/
int		input_file(t_root *root);
int		output_file(t_root *root);
int		checking_redirects(t_root *root, int *status);

/*==================command=============================*/
int		checking_processes(t_root *root);
char	*get_path(char **envp);
char	*find_path(char *final, char **paths);
int		do_command(t_root *root);
int		check_expander(t_root *r, t_ast **tree);
void	command_expander(t_ast **t, t_root *r);
int		check_dollar(char *str);
void	command_expander2(char *value, t_ast **tree, int *i);
/*expander 1*/
char	*creatingvalue2(char *cmd, char **temp);
char	**creatingvalue(char **split);

/*==================pipes==============================*/
int		counting_pipes(t_ast *tree);
int		*creating_pipes(t_ast *tree, int pipes);
int		child_in(t_root *root);
int		child_out(t_root *root);
int		doing_pipes(t_root *root);
int		checking_redirects_pipes(t_root *root, int i, int max);
t_ast	*checking_unfinishpipes(t_ast *tree);
void	deleting_tempfiles(t_ast *t);

#endif