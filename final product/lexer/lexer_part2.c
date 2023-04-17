/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:51:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/15 11:46:46 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*sign_node(int *i, char s, char *str)
{
	t_lexer	*node;

	node = NULL;
	if (str[*i] == str[*i + 1])
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
	{
		(*node)->next = sign_node(i, main[*i], main);
		//(*i)++;
	}
	else if (endofstring(main[*i]) && node_type(*node, main[*i]))
		return (error_syntax(&main[*i], 2));
	return (0);
}

char	*treating_quotes(char *str, char s, int *b)
{
	int		i;
	int		j;
	int		len;
	char	*test;

	j = *b;
	i = j + 1;
	while (str[i] != s)
		i++;
	len = i - j - 1;
	test = ft_substr(str, j + 1, len);
	*b = i;
	return (test);
}
