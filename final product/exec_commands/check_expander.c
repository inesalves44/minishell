/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:34:29 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/23 11:56:42 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_expander(t_ast **tree, t_root *r)
{
	char	*value;

	value = NULL;
	value = get_env_value(r, (*tree)->file + 1);
	free((*tree)->file);
	(*tree)->file = NULL;
	(*tree)->file = ft_strdup(value);
	free(value);
}

void	command_expander2(char *value, t_ast **tree, int i)
{
	free((*tree)->command[i]);
	(*tree)->command[i] = NULL;
	(*tree)->command[i] = ft_strdup(value);
	free(value);
}

void	command_expander(t_ast **t, t_root *r)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while ((*t)->command[i])
	{
		if (!ft_strncmp("$", (*t)->command[i], 1) && (*t)->squotes[i] == -1)
		{
			value = get_env_value(r, (*t)->command[i] + 1);
			if (is_equal((*t)->command[i] + 1, "?"))
			{
				free((*t)->command[i]);
				(*t)->command[i] = NULL;
				(*t)->command[i] = ft_strdup(ft_itoa(r->status_old));
			}
			else //if (value)
				command_expander2(value, t, i);
		}
		i++;
	}
}

int	check_expander(t_root *r, t_ast **t)
{
	if ((*t)->type == file)
	{
		if ((*t)->prev->type != here_doc && (*t)->file[0] == '$' \
		&& (*t)->squotes[0] == -1)
			file_expander(t, r);
	}
	else if ((*t)->type == command && !is_equal((*t)->command[0], "export"))
		command_expander(t, r);
	if ((*t)->left)
		check_expander(r, &(*t)->left);
	if ((*t)->rigth)
		check_expander(r, &(*t)->rigth);
	return (0);
}
