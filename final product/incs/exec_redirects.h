/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:47:25 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/18 17:49:28 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_REDIRECTS_H
# define EXEC_REDIRECTS_H

# include "../minishell.h"

/*==================redirects============================*/
int		input_file(t_root *root);
int		output_file(t_root *root);
int		checking_redirects(t_root *root, int *status);

/*command*/
int		checking_processes(t_root *root);
char	*get_path(char **envp);
char	*find_path(char *final, char **paths);
int		do_command(t_root *root);

/*pipes*/
int		counting_pipes(t_ast *tree);
int		*creating_pipes(t_ast *tree, int pipes);
int		child_in(t_root *root);
int		child_out(t_root *root);
int		doing_pipes(t_root *root);

#endif