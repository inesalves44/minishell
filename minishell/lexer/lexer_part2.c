/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:51:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/29 10:59:09 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Constructs lexer nodes based on the given 'split' string array, quote character 's',
 * and the initial index 'a'. It iterates through the split array, skipping empty strings,
 * and creates and links the lexer nodes accordingly using 'lexical_node'. The resulting
 * nodes are returned, with the 'node' pointer set to the head of the linked list.
 *
 * @param split The array of split tokens.
 * @param s     The quote character encountered.
 * @param i     The initial index.
 * @param a     The initial value for the index of the node.
 * @return      Returns a pointer to the constructed lexer nodes.
 */

t_lexer	*nodes_split2(char **split, char s, int i, int a)
{
	t_lexer	*node;

	node = NULL;
	while (split[i])
	{
		if (!ft_strncmp(split[i], " ", 1) && ft_strlen(split[i]) == 1)
			i++;
		else
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
			i++;
		}
	}
	while (node->prev)
		node = node->prev;
	return (node);
}

/**
 * Splits the given 'test' string using the quote character 's' as a delimiter,
 * and counts the number of tokens in the resulting split array. If the number
 * of tokens is 1, or if 'split_check' returns false, or if 'a' is 1, it returns
 * NULL after freeing the memory of the split array. Otherwise, it constructs the
 * lexer nodes by calling 'nodes_split2' and returns the resulting nodes.
 *
 * @param test The input string to split.
 * @param s    The quote character encountered.
 * @param a    The initial count of quote characters.
 * @return     Returns a pointer to the constructed lexer nodes.
 */

t_lexer	*nodes_split(char *test, char s, int a)
{
	t_lexer	*node;
	char	**split;
	int		i;

	i = 0;
	node = NULL;
	while (test[i] != '\0')
	{
		if (test[i] == s)
			a++;
		i++;
	}
	i = 0;
	split = ft_split(test, s);
	while (split[i])
		i++;
	if (i == 1 || !split_check(split) || a == 1)
	{
		free_str_split(split);
		return (NULL);
	}
	node = nodes_split2(split, s, 0, 0);
	free_str_split(split);
	return (node);
}

/**
 * Handles the processing of the first set of quotes encountered in the given 'str'.
 * It extracts the substring within the quotes using 'ft_substr' and constructs lexer
 * nodes by calling 'nodes_split' if necessary. The indices 'b' and 'j' are updated
 * accordingly, and the substring is returned.
 *
 * @param str  The input string to process.
 * @param b    A pointer to the current index in the string.
 * @param j    A pointer to the updated index within the substring.
 * @param node A pointer to the lexer node.
 * @return     Returns the extracted substring.
 */

char	*first_quotes(char *str, int *b, int *j, t_lexer **node)
{
	char	*test;
	char	s;
	int		len;

	s = str[*b];
	*j = *b;
	test = NULL;
	len = get_lenlexer(str, s);
	test = ft_substr(str, (*j) + 1, len - (*j) - 1);
	if (len == (int)ft_strlen(str) - 1)
	{
		*node = nodes_split(test, s, 0);
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
	(*b)++;
	return (test);
}

/**
 * Handles the processing of the second set of quotes encountered in the given 'test' string.
 * It iterates through the characters after the first quote until the closing quote is found,
 * and constructs the 'aux' string by concatenating the characters. If the resulting 'aux'
 * string has no significant characters (excluding spaces), it modifies 'test' accordingly.
 * Finally, it uses 'lexer_strjoin' to concatenate 'aux' with the remaining part of 'test',
 * updates 'test' with the new value, and frees 'aux'. The modified 'test' is then returned.
 *
 * @param j    A pointer to the updated index within the substring.
 * @param test The input string to process.
 * @param s    The quote character encountered.
 * @param str  The original string.
 * @return     Returns the modified 'test' string.
 */

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

/**
 * Processes quotes in the given 'str' string by extracting the substring within the quotes,
 * handling different cases, and constructing lexer nodes by calling 'treating_quotes2'.
 * The index 'b' is updated accordingly, and the resulting nodes are returned. If the
 * conditions for constructing lexer nodes are not met, it frees 'test' and returns a
 * single lexer node constructed using 'lexical_node'.
 *
 * @param str The input string to process.
 * @param s   The quote character encountered.
 * @param b   A pointer to the current index in the string.
 * @return    Returns a pointer to the constructed lexer nodes.
 */

t_lexer	*treating_quotes(char *str, char s, int *b)
{
	t_lexer	*node;
	int		j;
	char	*test;
	char	*test1;

	node = NULL;
	test = first_quotes(str, b, &j, &node);
	if (j == (int)ft_strlen (test) || \
	!closing_q2(test, test[j], j, ft_strlen(test)) || str[*b] == ' ' \
	|| str[*b] == 39 || str[*b] == 34)
	{
		(*b)--;
		if (!node)
			node = lexical_node(test, str[*b] + '0', *b);
		free(test);
		return (node);
	}
	test1 = second_quotes(&j, test, s, str);
	free(test);
	node = treating_quotes2(s, test1);
	*b = j;
	free(test1);
	return (node);
}
