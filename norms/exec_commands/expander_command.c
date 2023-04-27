/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:06:43 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/27 18:15:49 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*creatingvalue2(char s, char *cmd, int *i)
{
	char	*str;
	char	**split;

	str = NULL;
	split = ft_split(cmd, s);
	*i = 0;
	while (split[*i])
		(*i)++;
	if (*i > 1)
	{
		*i = 0;
		while (split[*i])
		{
			if (!str)
				str = ft_strdup(split[*i]);
			else
				str = ft_strjoin(str, split[*i]);
			(*i)++;	
		}
	}
	else
		str = ft_strdup(cmd);
	free_str_split(split);
	return (str);
}

char	*creatingvalue(char **cmd)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	str = NULL;
	temp = NULL;
	while (cmd[i])
	{
		str = creatingvalue2(split[0], ' ', *i);	
		
	}
	return (str);
}

char	*command_expander_2(t_root *r, int i)
{
	char	**split;
	char	*temp;
	char	*test;
	int		j;

	split = ft_split(r->tree->command[i], '$');
	split = creatingvalue(split);
	j = 0;
	test = ft_strdup("");
	while (split[j])
	{
		if (split[j][0] == '?')
			temp = ft_strdup(ft_itoa(r->status_old));
		else
			temp = get_env_value(r, split[j]);
		if (temp)
		{
			test = ft_strjoin(test, temp);
			free(temp);
		}
		j++;
	}
	return (test);
}

void	command_expander(t_ast **t, t_root *r)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while ((*t)->command[i])
	{
		if (check_dollar((*t)->command[i]) && (*t)->squotes[i] == -1)
		{
			value = command_expander_2(r, i);
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
			if (value)
				free(value);
		}
		i++;
	}
}
