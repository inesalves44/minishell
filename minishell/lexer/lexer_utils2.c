/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:59:00 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/29 11:19:22 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Checks for a specific signal character in the 'main' string at index 'i'. If the character
 * matches '|', it calls the 'error_syntax' function with the corresponding error code (2) ---> its a syntax error if 
 * a pipe is in the firt position.
 * Then, it calls the 'sign_node' function to create a lexer node based on the signal character,
 * and assigns it to the 'node' pointer. If a lexer node is created, 'i' is incremented. Finally,
 * it returns 0.
 *
 * @param main The main string to check.
 * @param i    The current index in the string.
 * @param node The lexer node pointer to assign the created node.
 * @return     Returns 0.
 */

int	check_signal1(char *main, int *i, t_lexer **node)
{
	if (main[*i] == '|')
		return (error_syntax(&main[*i], 2));
	*node = sign_node(i, main[*i], main);
	if (*node != NULL)
		(*i)++;
	return (0);
}

/**
 * Checks for a signal character in the 'main' string at index 'i'. If the character is a space
 * or the end of the string, it returns 0. If the character is the end of a string and does not
 * match the type of the current 'node', it calls the 'sign_node' function to create a lexer node
 * and assigns it to the 'next' pointer of the 'node'. If the character is the end of a string and
 * matches the type of the 'node', it calls the 'error_syntax' function with the corresponding
 * error code (2). Finally, it returns 0.
 *
 * @param main The main string to check.
 * @param i    The current index in the string.
 * @param node The lexer node pointer.
 * @return     Returns 0.
 */

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

/**
 * Creates a lexer node based on the signal character 's' at index 'i' in the 'str' string. If the
 * character is '<' or '>', and the next character is the same, it creates a lexer node with the
 * corresponding type (here_doc or app_out) and assigns it to the 'node'. 'i' is incremented to
 * skip the next character, and the created node is returned. If the character is '|', '<', or '>',
 * it creates a lexer node with the corresponding type (pipem, red_in, or red_out) and assigns it
 * to the 'node'. The created node is then returned.
 *
 * @param i   The current index in the string.
 * @param s   The signal character.
 * @param str The input string.
 * @return    Returns the newly created lexer node or NULL if no node is created.
 */

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

/**
 * Checks if there is a closing quote character 'c' after the current index 'i' in the 'str' string.
 * The function iterates through the string starting from index 'i+1' and checks if any character
 * matches 'c'. If a matching character is found, it returns 1, indicating the presence of a closing
 * quote. Otherwise, it returns 0.
 *
 * @param str The input string to check.
 * @param c   The quote character to match.
 * @param i   The current index in the string.
 * @param len The length of the string.
 * @return    Returns 1 if a closing quote is found, 0 otherwise.
 */

int	closing_q2(char *str, char c, int i, int len)
{
	i++;
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * Concatenates two strings 's1' and 's2' using dynamic memory allocation. It calculates the
 * lengths of both strings using 'ft_strlen', allocates memory for the new string 'str', and
 * copies the content of 's1' and 's2' using 'ft_strlcpy' and 'ft_strlcat'. The resulting string
 * is terminated with a null character. The function then frees the memory allocated for 's1'
 * and returns the new string 'str'.
 *
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 * @return   Returns the concatenated string.
 */

char	*lexer_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1)
		return (NULL);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, len1 + 1);
	ft_strlcat(str, (char *)s2, len2 + len1 + 1);
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}
