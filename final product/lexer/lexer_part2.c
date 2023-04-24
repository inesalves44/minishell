/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:51:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/22 14:50:32 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*sign_node(int *i, char s, char *str)
{
	t_lexer	*node;

	node = NULL;
	if (str[*i] == str[*i + 1] && (str[*i] == '<' || str[*i] == '>'))
	{
		if (s == '<')
			node = lexical_node(NULL, here_doc, *i);
		else
			node = lexical_node(NULL, app_out, *i);
		(*i)++;
		return (node);
	}
	if (s == '|')
		node = lexical_node(NULL, pipem, *i);
	else if (s == '<')
		node = lexical_node(NULL, red_in, *i);
	else if (s == '>')
		node = lexical_node(NULL, red_out, *i);
	return (node);
}

int	check_signal1(char *main, int *i, t_lexer **node)
{
	if (main[*i] == '|')
		return (error_syntax(&main[*i], 2));
	*node = sign_node(i, main[*i], main);
	if (*node != NULL)
		(*i)++;
	return (0);
}

int	check_signal(char *main, int *i, t_lexer **node)
{
	if (main[*i] == ' ' || main[*i] == '\0')
		return (0);
	if (endofstring(main[*i]) && !node_type(*node, main[*i]))
		(*node)->next = sign_node(i, main[*i], main);
	else if (endofstring(main[*i]) && node_type(*node, main[*i]))
		return (error_syntax(&main[*i], 2));
	return (0);
}

t_lexer	*treating_quotes(char *str, char s, int *b)
{
	t_lexer	*node;
	int		j;
	int		a;
	int		c;
	int		len;
	char	*test;
	char	*aux;
	char	*aux2;
	char	**split;

	j = *b;
	len = ft_strlen(str) - 1;
	while (str[len] != s)
		len--;
	test = ft_substr(str, j + 1, len - j - 1);
	j = 0;
	while (test[j] != s && test[j] != '\0')
		j++;
	if (j == (int)ft_strlen (test) || !closing_q2(test, test[j], j, ft_strlen(test)))
	{
		*b = len;
		node = lexical_node(test, str[*b] + '0', *b);
		free(test);
		return (node);
	}
	c = j;
	j++;
	a = 0;
	while (test[j] != s && test[j] != '\0')
	{
		if (test[j] != ' ')
			a++;
		j++;
	}
	if (a == 0)
		aux = ft_substr(test, 0, c);
	aux2 = malloc(sizeof(char) * 2);
	aux2[0] = ' ';
	aux2[1] = '\0';
	aux = ft_strjoin(aux, aux2); 
	test = ft_strjoin(aux, ft_substr(test, j + 1, len));
	*b = len;
	split = ft_split(test, ' ');
	node = lexical_node(split[0], str[*b] + '0', *b);
	node->next = lexical_node(split[1], str[*b] + '0', *b);
	node->next->prev = node;
	node = node->next;
	free(test);
	free(aux);
	free(aux2);
	return (node);
}
