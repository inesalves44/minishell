/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:34:29 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/27 10:09:23 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_expander(t_ast **tree, t_root *r)
{
	char	*value;

	value = NULL;
	value = get_env_value(r, (*tree)->file + 1);
	if (!value)
		return (e_pro(": ambiguous redirect", *tree, 1, 0));
	free((*tree)->file);
	(*tree)->file = NULL;
	(*tree)->file = ft_strdup(value);
	free(value);
	return (0);
}

char	**final_str(char **split, t_ast **tree, int len, int i)
{
	int		a;
	int		b;
	int		j;
	char	**final;

	final = (char **)malloc(sizeof(char *) * (len + 1));
	j = 0;
	b = 0;
	while (j < len)
	{
		if (i == j)
		{
			a = 0;
			while (split[a])
			{
				final[j] = ft_strdup(split[a]);
				a++;
				j++;
			}
			b++;
		}
		else
		{
			final[j] = ft_strdup((*tree)->command[b]);
			b++;
			j++;
		}
	}
	final[j] = 0;
	return (final);
}

char	**complete_command(char **final, int len)
{
	char	**str;
	int		j;

	str = NULL;
	str = (char **)malloc(sizeof(char *) * (len + 1));
	j = 0;
	while (j < len)
	{
		str[j] = ft_strdup(final[j]);
		j++;
	}
	str[j] = 0;
	return (str);
}

void	command_expander2(char *value, t_ast **tree, int i)
{
	char	**split;
	char	**final;
	int		j;
	int		len;

	j = 0;
	split = NULL;
	final = NULL;
	if (value)
		split = ft_split(value, ' ');
	while (split[j])
		j++;
	len = j;
	j = 0;
	while ((*tree)->command[j])
		j++;
	len = len + j - 1;
	final = final_str(split, tree, len, i);
	free_str_split((*tree)->command);
	(*tree)->command = NULL;
	(*tree)->command = complete_command(final, len);
	free_str_split(split);
	free_str_split(final);
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
			else if (value)
				command_expander2(value, t, i);
			else if(!value)
				(*t)->command[i] = ft_strdup("");
			free(value);
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
			r->status = file_expander(t, r);
	}
	else if ((*t)->type == command && (*t)->command && !is_equal((*t)->command[0], "export"))
		command_expander(t, r);
	if ((*t)->left)
		check_expander(r, &(*t)->left);
	if ((*t)->rigth)
		check_expander(r, &(*t)->rigth);
	if (r->status)
		return (r->status);
	return (0);
}
