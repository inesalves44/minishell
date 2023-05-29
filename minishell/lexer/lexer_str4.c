/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:53:08 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/29 10:47:33 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Creates a modified string based on the given 'line' by extracting a substring
 * using the 'start_str' function, then calling 'aux_quotes' to process additional quotes,
 * and finally concatenating the extracted substring and processed quotes using 'complete_strlexer'.
 * The character 's' is updated to store the quote character encountered.
 *
 * @param line The input line to process.
 * @param i    A pointer to the current index in the line.
 * @param len  The length of the line.
 * @param s    A pointer to the quote character encountered.
 * @return     Returns a pointer to the modified string.
 */

char	*create_string4(char *line, int *i, int len, char *s)
{
	char	*aux;
	char	*str;
	char	*str2;

	str = NULL;
	str2 = NULL;
	aux = NULL;
	str = start_str(line, i, len);
	if (*i == len)
		return (str);
	*s = line[*i];
	aux = aux_quotes(line, i, len, *s);
	str2 = complete_strlexer(str, aux);
	if (str)
		free(str);
	free(aux);
	*s = change_q(*s);
	return (str2);
}

/**
 * Builds the final auxiliary string by processing different cases based on the given 'line',
 * 'aux', 'len', and 'i'. It treats the beginning and end of the line, calls 'create_string3'
 * if necessary, and then concatenates 'aux' and 'str' using 'ft_strjoin'.
 *
 * @param line The input line to process.
 * @param aux  The auxiliary string to concatenate.
 * @param len  The length of the line.
 * @param i    A pointer to the current index in the line.
 * @return     Returns a pointer to the final auxiliary string.
 */

char	*final_aux(char *line, char *aux, int len, int *i)
{
	char	*str;
	char	*str1;

	str = NULL;
	str1 = NULL;
	str = treat_begin(line, len);
	str = treat_end(line, len, *i);
	if (!str)
		str = create_string3(line, i, len);
	if (aux && str)
		str1 = ft_strjoin(aux, str);
	else if (!aux && str)
		str1 = ft_strdup(str);
	else if (aux && !str)
		str1 = ft_strdup(aux);
	if (str)
		free(str);
	return (str1);
}

/**
 * Determines the length of the lexer by finding the index of the character 's'
 * in the given 'str' and subtracting from the length.
 *
 * @param str The input string.
 * @param s   The character to find.
 * @return    Returns the length of the lexer.
 */

int	get_lenlexer(char *str, char s)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (str[len] != s)
		len--;
	return (len);
}

/**
 * Treats quotes by splitting the given 'test' string using space as a delimiter,
 * then calling 'nodes_split2' to process the split tokens and construct the lexer nodes.
 *
 * @param s    The quote character encountered.
 * @param test The input string to process.
 * @return     Returns a pointer to the constructed lexer node.
 */

t_lexer	*treating_quotes2(char s, char *test)
{
	char	**split;
	t_lexer	*node;

	split = ft_split(test, ' ');
	node = nodes_split2(split, s, 0, 0);
	free_str_split(split);
	return (node);
}

/**
 * Checks if there is a signal in the given 'str' by calling 'check_signal'.
 * If a signal is found, frees the memory of 'str' and returns 2.
 *
 * @param str  A pointer to the string to check.
 * @param i    A pointer to the current index.
 * @param node A pointer to the lexer node.
 * @return     Returns 2 if a signal is found, otherwise 0.
 */

int	check_signal3(char **str, int *i, t_lexer **node)
{
	if (check_signal(*str, i, node))
	{
		free(*str);
		*str = NULL;
		return (2);
	}
	return (0);
}
