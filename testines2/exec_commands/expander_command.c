/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:06:43 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/03 09:35:06 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_test2(char *test, char **temp)
{
	char	*final;

	final = NULL;
	final = ft_strjoin_gnl(test, *temp);
	free(*temp);
	*temp = NULL;
	return (final);
}

char	*create_test(char **s, char *temp, t_root *r, int i)
{
	int		j;
	char	*test;

	j = 0;
	test = NULL;
	while (s[j])
	{
		if (j > 0 && s[j][0] == '?' && s[j - 1][0] == '$')
			temp = ft_strdup(ft_itoa(r->status_old));
		else if (j == 1 && r->tree->command[i][0] != '$')
			temp = ft_strdup(s[j]);
		else if (j > 0 && s[j - 1][0] == '$' && s[j][0] != 34 && s[j][0] != 39)
			temp = get_env_value(r, s[j]);
		else if (!is_equal(s[j], "$"))
			temp = ft_strdup(s[j]);
		if (temp)
			test = create_test2(test, &temp);
		j++;
	}
	if (temp)
		free(temp);
	return (test);
}

char	*command_expander_2(t_root *r, int i)
{
	char	**split;
	char	**split2;
	char	*test;

	split2 = ft_split(r->tree->command[i], '$');
	split = creatingvalue(split2);
	//free_str_split(split2);
	//test = ft_strdup(""); //
	test = create_test(split, NULL, r, i);
	free_str_split(split); //back with this line
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
		if (check_dollar((*t)->command[i]) && (*t)->squotes[i] == -1 && !is_equal((*t)->command[i], "$"))
		{
			value = command_expander_2(r, i);
			if (!is_equal(value, ""))
				command_expander2(value, &i, r);
			else
				(*t)->command[i] = ft_strdup("");
			if (value)
				free(value);
		}
		i++;
	}
}

void	get_quotes(t_root *r, char **split)
{
	int	*squotes;
	int	*dquotes;

	r->a = 0;
	r->b = 0;
	r->j = 0;
	get_quotes2(&squotes, &dquotes, r, split);
	free(r->tree->dquotes);
	free(r->tree->squotes);
	r->j = 0;
	r->tree->squotes = (int *)malloc(sizeof(int) * r->len);
	r->tree->dquotes = (int *)malloc(sizeof(int) * r->len);
	while (r->j < r->len)
	{
		r->tree->squotes[r->j] = squotes[r->j];
		r->tree->dquotes[r->j] = dquotes[r->j];
		(r->j)++;
	}
	free(squotes);
	free(dquotes);
}