/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:40:42 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/25 18:57:13 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_string2(char *line, int *i, int *len1)
{
	int	b;

	b = 1;
	while (line[*len1] == line[*len1 - 1] && line[*i] == line[*i + 1])
	{
		(*len1)--;
		(*i)++;
		b++;
	}
	if (b % 2 == 0)
	{
		(*i)++;
		(*len1)--;
	}
}

char	*find_string(char *line, int *i, int len)
{
	char	s;
	int		len1;
	int		test;
	char	*aux;

	s = line[*i];
	len1 = len - 1;
	while (line[len1] != s)
		len1--;
	test = len1;
	find_string2(line, i, &len1);
	if (len1 > *i)
		aux = ft_substr(line, *i, len1 - *i + 1);
	*i = test + 1;
	return (aux);
}

char	*auxquotes2(char *line, int *i, int len, char s)
{
	int		c;
	char	*aux;

	aux = find_string(line, i, len);
	if (aux && aux[0] == s)
	{
		c = 1;
		aux = create_string3(aux, &c, ft_strlen(aux) - 1);
		if (aux)
			aux = add_quotes(s, aux);
	}
	else if (aux && aux[0] != s)
	{
		c = 0;
		aux = create_string3(aux, &c, ft_strlen(aux));
	}
	return (aux);
}

char	*aux_quotes(char *line, int *i, int len, char s)
{
	char	*aux;
	int		a;

	aux = NULL;
	if (closing_q2(line, line[*i], *i, len))
		aux = auxquotes2(line, i, len, s);
	else
	{
		a = *i;
		(*i)++;
		while (line[*i] != 34 && line[*i] != 39 && *i < len)
			(*i)++;
		aux = ft_substr(line, a, *i - a);
	}
	return (aux);
}
