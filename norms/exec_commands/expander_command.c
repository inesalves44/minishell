/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:06:43 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/28 12:36:04 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*creatingvalue2(char *cmd, char **temp)
{
	char	*str;
	int		j;
	int		a;

	j = 0;
	if (cmd[j] == ' ' || cmd[j] == 34 || cmd[j] == 39)
	{
		*temp = ft_strdup("");
		return (cmd);
	}
	while (cmd[j] != '\0')
	{
		if (cmd[j] == ' ' || cmd[j] == 34 || cmd[j] == 39)
			break ;
		j++;
	}
	a = j;
	str = ft_substr(cmd, 0, j);
	while (cmd[j])
		j++;
	if (a < j)
		*temp = ft_substr(cmd, a, j);
	else
		*temp = ft_strdup("");
	free(cmd);
	return (str);
}

char	**creatingvalue(char **split)
{
	char	**split3;
	char 	*str;
	char	**split2;
	int		i;

	i = 0;
	while (split[i])
		i++;
	split3 = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (split[i])
	{
		split[i] = creatingvalue2(split[i], &str);
		split3[i] = ft_strdup(str);
		free(str);
		str = NULL;
		i++;
	}
	split3[i] = 0;
	int len = i * 2 + 1;
	if (i % 2 == 0)
		len += i;
	else
		len = len + i - 1;
	i = 0;
	split2 = (char **)malloc(sizeof(char *) * (len));
	int j = 0;
	i = 0; 
	while (i < len - 1)
	{
		split2[i] = ft_strdup("$");
		i++;
		split2[i] = ft_strdup(split[j]);
		i++;
		split2[i] = ft_strdup(split3[j]);
		j++;
		i++;
	}
	split2[i] = 0;
	free_str_split(split);
	free_str_split(split3);
	return (split2);
}

char	*command_expander_2(t_root *r, int i)
{
	char	**split;
	char	**split2;
	char	*temp;
	char	*test;
	int		j;

	split2 = ft_split(r->tree->command[i], '$');
	split = creatingvalue(split2);
	//free_str_split(split2);
	j = 0;
	temp = NULL;
	test = ft_strdup("");
	while (split[j])
	{
		if (j > 0 && split[j][0] == '?' && split[j - 1][0] == '$')
			temp = ft_strdup(ft_itoa(r->status_old));
		else if (j > 0 && split[j - 1][0] == '$' && split[j][0] != 34 && split[j][0] != 39)
			temp = get_env_value(r, split[j]);
		else if (!is_equal(split[j], "$"))
			temp = ft_strdup(split[j]);
		if (temp)
		{
			test = ft_strjoin(test, temp);
			free(temp);
			temp = NULL;
		}
		j++;
	}
	if (temp)
		free(temp);
	//free_str_split(split);
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
			if (!is_equal(value, ""))
				command_expander2(value, t, i);
			else
				(*t)->command[i] = ft_strdup("");
			if (value)
				free(value);
		}
		i++;
	}
}
