/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:08:03 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/28 19:39:54 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "libft/incs/libft.h"
# include "libft/incs/ft_printf.h"
# include "libft/incs/get_next_line.h"

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

#endif
