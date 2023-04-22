/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:58:38 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/22 14:36:07 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*first_node(char *main, int *i, char **test)
{
	t_lexer	*node;
	int		start;
	int		len;

	start = *i;
	if (endofquotes(main[*i]))
		(*i)++;
	while (!endofstring(main[*i]))
		(*i)++;
	len = *i - start;
	*test = ft_substr(main, start, len);
	node = lexical_node(*test, 0, start);
	return (node);
}

int check_spaces(char *test)
{
	int	i;

	i = 0;
	while (test[i] != '\0')
	{
		if (test[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_firstnode(char *main, int *i, t_lexer **node)
{
	char	*test;
	char	**split;
	int		a;

	a = 0;
	*node = NULL;
	while (main[*i] == ' ')
		(*i)++;
	if (check_signal1(main, i, node))
		return (2);
	if (*node != NULL)
		return (0);
	if (endofquotes(main[*i]) && closing_q(main, main[*i], *i, &a))
	{
		test = treating_quotes(main, main[*i], i);
		if (check_spaces(test))
		{
			split = ft_split(test, ' ');
			*node = lexical_node(split[0], main[*i] + '0', *i);
			(*node)->next = lexical_node(split[1], main[*i] + '0', *i);
			(*node)->next->prev = *node;
			*node = (*node)->next;
		}
		else
			*node = lexical_node(test, main[*i] + '0', *i);
		(*i)++;
	}
	else
		*node = first_node(main, i, &test);
	free(test);
	return (0);
}

void	add_index(t_lexer **node)
{
	int	i;

	while ((*node)->prev)
		*node = (*node)->prev;
	i = 0;
	while (*node)
	{
		(*node)->number = i;
		if (!(*node)->next)
			break ;
		*node = (*node)->next;
		i++;
	}
	while ((*node)->prev)
		*node = (*node)->prev;
}

t_lexer	*node_str(char *str, int *i, int j)
{
	t_lexer	*node;
	char	*test;
	char	**split;
	int		a;

	a = 0;
	if (endofquotes(str[*i]) && closing_q(str, str[*i], *i, &a) && str[*i - 1] == ' ')
	{
		test = treating_quotes(str, str[*i], i);
		if (check_spaces(test))
		{
			split = ft_split(test, ' ');
			node = lexical_node(split[0], str[*i] + '0', *i);
			node->next = lexical_node(split[1], str[*i] + '0', *i);
			node->next->prev = node;
			node = node->next;
		}
		else
			node = lexical_node(test, str[*i] + '0', *i);
		//(*i)++;
	}
	else
	{
		while (!endofstring(str[*i]))
			(*i)++;
		test = ft_substr(str, j, *i - j);
		(*i)--;
		node = lexical_node(test, 0, j);
	}
	free (test);
	return (node);
}

int	lexical_annalysis(t_lexer **node, char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = create_string(line);
	if (!str)
		return (1);
	if (check_firstnode(str, &i, node))
		return (2);
	while (str[i] != '\0')
	{
		j = i;
		if (check_signal(str, &i, node))
			return (2);
		if (!(*node)->next && str[i] != ' ')
			(*node)->next = node_str(str, &i, j);
		if ((*node)->next)
		{
			(*node)->next->prev = *node;
			*node = (*node)->next;
		}
		i++;
	}
	add_index(node);
	return (0);
}

	/*int test2 = 1;
	while (*node)
	{
		printf("------------number: %d-----------\n", (*node)->number);
		printf("value of node: %d\n", (*node)->type);
		if ((*node)->str)
			printf("string of the node: %s\n", (*node)->str);
		test2++;
		if (!(*node)->next)
			break ;
		(*node) = (*node)->next;
	}
	while ((*node)->prev)
		(*node) = (*node)->prev;*/

	/*str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (a < len)
	{
		str[a] = main[i];
		a++;
		i++;
	}
	str[a] = '\0';*/

/*	char	*treating_str1(char *main, int i, int j)
{
	char	*str;
	int		len;

	len = j - i;
	str = ft_substr(main, i, len);
	return (str);
}*/

/*//(char *)malloc(sizeof(char) * (len));
	a = 0;
	while (a < len - 1)
	{
		test[a] = str[j + 1];
		a++;
		j++;
	}
	test[a] = '\0';*/
