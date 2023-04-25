/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:51:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/25 20:15:08 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*first_quotes(char *str, char s, int *b, int *j)
{
	char	*test;
	int		len;

	*j = *b;
	test = NULL;
	len = ft_strlen(str) - 1;
	while (str[len] != s)
		len--;
	test = ft_substr(str, (*j) + 1, len - (*j) - 1);
	*b = len;
	*j = 0;
	while (test[*j] != s && test[*j] != '\0')
		(*j)++;
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
		j++;
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

	test = first_quotes(str, s, b, &j);
	if (j == (int)ft_strlen (test) || \
	!closing_q2(test, test[j], j, ft_strlen(test)))
	{
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
