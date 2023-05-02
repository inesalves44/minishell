/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_commands2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:28:46 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/02 21:28:20 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_ints(int *a, int *j, int *b)
{
	*j = 0;
	*a = 0;
	*b = 0;
}

char	**final_str2(t_ast **tree, int i, char **split, char **final, int len)
{
	int	a;
	int	j;
	int b;

	start_ints(&a, &j, &b);
	while (j < len)
	{
		if (i == j)
		{
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
	return (final);
}

char	**final_str(char **split, t_ast **tree, int len, int i)
{
	char	**final;

	final = (char **)malloc(sizeof(char *) * (len + 1));
	final = final_str2(tree, i, split, final, len);
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

void	get_quotes(t_ast **tree, int i, char **split, int len)
{
	int	*squotes;
	int	*dquotes;
	int	j;
	int	b;
	int	a;

	j = 0;
	b = 0;
	a = 0;
	squotes = (int *)malloc(sizeof(int) * len);
	dquotes = (int *)malloc(sizeof(int) * len);
	while (j < len)
	{
		if (i == j)
		{
			while (split[a])
			{
				squotes[j] = (*tree)->squotes[b];
				dquotes[j] = (*tree)->dquotes[b];
				a++;
				j++;
			}
			b++;
		}
		else
		{
			squotes[j] = (*tree)->squotes[b];
			dquotes[j] = (*tree)->dquotes[b];
			j++;
			b++;
		}
	}
	free((*tree)->dquotes);
	free((*tree)->squotes);
	j = 0;
	(*tree)->squotes = (int *)malloc(sizeof(int) * len);
	(*tree)->dquotes = (int *)malloc(sizeof(int) * len);
	while (j < len)
	{
		(*tree)->squotes[j] = squotes[j];
		(*tree)->dquotes[j] = dquotes[j];
		j++;
	}
	free(squotes);
	free(dquotes);
}

void	command_expander2(char *value, t_ast **tree, int *i)
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
	final = final_str(split, tree, len, *i);
	final[len] = 0;
	get_quotes(tree, *i, split, len);
	free_str_split((*tree)->command);
	(*tree)->command = NULL;
	(*tree)->command = complete_command(final, len);
	free_str_split(split);
	free_str_split(final);
	*i = 0;
}
