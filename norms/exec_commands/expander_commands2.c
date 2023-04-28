/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_commands2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:28:46 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/28 12:36:27 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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