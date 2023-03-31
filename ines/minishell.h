/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:08:03 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/31 19:21:12 by idias-al         ###   ########.fr       */
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

typedef enum types
{
    pipem,
    red_in,
    red_out,
    command,
    file,
} check;

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

char	*get_file(char **str, t_ast *node);
char	**treat_string(char **str, t_ast *aux, int i);
t_ast	*create_treenode(char **str, int check, int i, t_ast *aux);
void	print_tree(t_ast *node, int i, char **str);
t_ast	*parsing_str(char **str);
char	*get_path(char **envp);
char	*find_path(char *final, char **paths);
void	do_command(t_ast *tree, int in, int out, char *envp[]);

#endif
