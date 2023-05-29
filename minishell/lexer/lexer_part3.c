/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:46:37 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/29 11:07:39 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Checks if there are only spaces within the given 'test' string. It iterates through
 * the characters in the string, and if it encounters quotes ('"' or "'"), it skips the
 * characters between the quotes. If a non-space character is found outside of the quotes,
 * it returns 0. Otherwise, if only spaces are found, it returns 1.
 *
 * @param test The input string to check.
 * @return     Returns 1 if there are only spaces, 0 otherwise.
 */

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

/**
 * Creates an auxiliary string by extracting the substring between the indices 'a' and 'len'
 * from the given 'str' string. The index 'i' is updated to 'len', and the resulting auxiliary
 * string is returned.
 *
 * @param str The input string to extract the substring from.
 * @param i   A pointer to the current index in the string.
 * @param len The length of the string.
 * @return    Returns the extracted auxiliary string.
 */

char	*create_aux(char *str, int *i, int len)
{
	char	*aux;
	int		a;

	aux = NULL;
	a = (*i);
	while (!endofstring(str[*i]) && !endofquotes(str[*i]))
		(*i)++;
	aux = ft_substr(str, a + 1, len - *i - 1);
	*i = len;
	return (aux);
}

/**
 * Handles the processing of the 'str' string when encountering the closing quote. If the closing
 * quote is followed by characters that indicate the presence of another quote, it extracts the
 * appropriate substring using 'ft_substr' and updates the index 'i'. Otherwise, it creates the
 * auxiliary string using 'create_aux' and checks if it contains significant characters. If so,
 * it concatenates the auxiliary string with 'test' using 'lexer_strjoin'. Finally, it frees the
 * auxiliary string and returns the modified 'test' string.
 *
 * @param str  The input string to process.
 * @param i    A pointer to the current index in the string.
 * @param test The existing 'test' string.
 * @param s    The quote character encountered.
 * @return     Returns the modified 'test' string.
 */

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
		*i = len +1;
	}
	else
		aux = create_aux(str, i, len);
	if (aux)
	{
		if (aux_space(aux))
			test = lexer_strjoin(test, aux);
		free(aux);
	}
	return (test);
}

/**
 * Constructs a lexer node based on the given 'str' string, index 'i', and initial index 'j'.
 * It checks if the string ends with quotes and if there are closing quotes present, and
 * constructs lexer nodes accordingly using 'treating_quotes' or 'lexical_node'. If quotes
 * are not encountered, it constructs a lexer node using 'lexical_node'. The resulting node
 * is returned.
 *
 * @param str The input string to process.
 * @param i   A pointer to the current index in the string.
 * @param j   The initial index.
 * @return    Returns a pointer to the constructed lexer node.
 */

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
		(*i)++;
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

/**
 * Checks the split array for empty strings. It iterates through the array and counts the number
 *of spaces.
 * @param a string of strings.
 * @return number of spaces
*/

int	split_check(char **split)
{
	int	b;
	int	i;

	i = 0;
	b = 0;
	while (split[i])
	{
		if (!ft_strncmp(split[i], " ", 1))
			b++;
		i++;
	}
	return (b);
}
