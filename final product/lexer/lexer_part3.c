/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:46:37 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/26 13:19:30 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spaces(char *test)
{
	int		i;
	char	s;

	i = 0;
	while (test[i] != '\0')
	{
		if (test[i] == 34 || test[i] == 39)
		{
			s = test[i];
			i++;
			while (test[i] != s)
			{
				if (test[i] != ' ')
					return (0);
				i++;
			}
		}
		i++;
	}
	return (1);
}

char	*create_aux(char *str, int *i, int len)
{
	char	*aux;
	int		a;

	aux = NULL;
	a = (*i);
	while (!endofstring(str[*i]) && !endofquotes(str[*i]))
		(*i)++;
	aux = ft_substr(str, a + 1, len - *i - 1);
	return (aux);
}

char	*test2(char *str, int *i, char *test, char s)
{
	int		len;
	char	*aux;

	len = ft_strlen(str);
	if (closing_q2(str, str[*i], *i, ft_strlen(str)))
	{
		(*i)++;
		len--;
		while (str[len] != s)
			len--;
		aux = ft_substr(str, *i, len - *i);
	}
	else
		aux = create_aux(str, i, len);
	if (aux)
	{
		test = lexer_strjoin(test, aux);
		free(aux);
	}
	(*i) = len + 1;
	return (test);
}

t_lexer	*node_str(char *str, int *i, int j)
{
	t_lexer	*node;
	char	*test;
	int		a;

	a = 0;
	test = NULL;
	if (endofquotes(str[*i]) && closing_q(str, str[*i], *i, &a) \
	&& str[*i - 1] == ' ')
		node = treating_quotes(str, str[*i], i);
	else
	{
		while (!endofstring(str[*i]) && !endofquotes(str[*i]))
			(*i)++;
		test = ft_substr(str, j, *i - j);
		if (endofquotes(str[*i]))
			test = test2(str, i, test, str[*i]);
		(*i)--;
		node = lexical_node(test, 0, j);
	}
	if (test)
		free (test);
	return (node);
}
