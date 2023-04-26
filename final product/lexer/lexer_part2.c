/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:51:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/26 15:15:28 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*nodes_split2(char **split, char s)
{
	t_lexer	*node;
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], " ", 1))
		{
			if (!node)
				node = lexical_node(split[i], s + '0', a);
			else
			{
				node->next = lexical_node(split[i], s + '0', a);
				node->next->prev = node;
				node = node->next;
			}
			a++;
		}
		i++;
	}
	return (node);
}

t_lexer	*nodes_split(char *test, char s)
{
	t_lexer	*node;
	char	**split;
	int		i;

	i = 0;
	node = NULL;
	split = ft_split(test, s);
	while (split[i])
		i++;
	if (i == 1 || !split_check(split))
	{
		free_str_split(split);
		return (NULL);
	}
	i = 0;
	node = nodes_split2(split, s);
	free_str_split(split);
	return (node);
}

char	*first_quotes(char *str, int *b, int *j, t_lexer **node)
{
	char	*test;
	char	s;
	int		len;

	s = str[*b];
	*j = *b;
	test = NULL;
	len = ft_strlen(str) - 1;
	while (str[len] != s)
		len--;
	test = ft_substr(str, (*j) + 1, len - (*j) - 1);
	if (len == (int)ft_strlen(str) - 1)
	{
		*node = nodes_split(test, s);
		*j = ft_strlen(test);
		*b = len;
	}
	else
	{
		*j = 0;
		while (test[*j] != s && test[*j] != '\0')
			(*j)++;
		*b = len;
	}
	return (test);
}

char	*second_quotes(int *j, char *test, char s, char *str)
{
	int		a;
	int		c;
	char	*aux;
	char	*aux2;

	c = *j;
	(*j)++;
	a = 0;
	while (test[*j] != s && test[*j] != '\0')
	{
		if (test[*j] != ' ')
			a++;
		(*j)++;
	}
	if (a == 0)
		aux = ft_substr(test, 0, c);
	aux2 = malloc(sizeof(char) * 2);
	aux2[0] = ' ';
	aux2[1] = '\0';
	aux = ft_strjoin(aux, aux2);
	test = lexer_strjoin(aux, ft_substr(test, *j + 1, ft_strlen(str) - 1));
	free(aux2);
	return (test);
}

t_lexer	*treating_quotes(char *str, char s, int *b)
{
	t_lexer	*node;
	int		j;
	char	*test;
	char	**split;

	node = NULL;
	test = first_quotes(str, b, &j, &node);
	if (j == (int)ft_strlen (test) || \
	!closing_q2(test, test[j], j, ft_strlen(test)))
	{
		if (!node)
			node = lexical_node(test, str[*b] + '0', *b);
		free(test);
		return (node);
	}
	test = second_quotes(&j, test, s, str);
	split = ft_split(test, ' ');
	node = lexical_node(split[0], str[*b] + '0', *b);
	node->next = lexical_node(split[1], str[*b] + '0', *b);
	node->next->prev = node;
	node = node->next;
	free(test);
	free_str_split(split);
	return (node);
}
