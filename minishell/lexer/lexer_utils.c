/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:54:40 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/29 11:12:29 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Creates a new lexer node with the given 'str' string, 'type' value, and 'j' number. The function
 * allocates memory for the node, duplicates the string using 'ft_strdup', and assigns the 'type'
 * and 'number' values. The 'next' and 'prev' pointers are initialized to NULL. The resulting node
 * is returned.
 *
 * @param str   The string value for the lexer node.
 * @param type  The type value for the lexer node.
 * @param j     The number value for the lexer node.
 * @return      Returns a pointer to the newly created lexer node.
 */

t_lexer	*lexical_node(char *str, int type, int j)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (node)
	{
		if (str)
			node->str = ft_strdup(str);
		else
			node->str = NULL;
		node->type = type;
		node->number = j;
		node->next = NULL;
		node->prev = NULL;
	}
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
 * @param a   A placeholder value (unused in the function). -----> not necessary!
 * @return    Returns 1 if a closing quote is found, 0 otherwise.
 */

int	closing_q(char *str, char c, int i, int *a)
{
	(void)a;
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * Checks if the given character 's' represents the end of a string. It compares 's' against
 * various characters that indicate the end of a token or string. If 's' matches any of these
 * characters, the function returns 1. Otherwise, it returns 0.
 *
 * @param s The character to check.
 * @return  Returns 1 if 's' represents the end of a string or token, 0 otherwise.
 */

int	endofstring(char s)
{
	if (s == '\0')
		return (1);
	else if (s == ' ')
		return (1);
	else if (s == '|')
		return (1);
	else if (s == '<')
		return (1);
	else if (s == '>')
		return (1);
	return (0);
}

/**
 * Checks if the given character 's' represents the end of quotes. It compares 's' against the
 * ASCII values of double quotes (34) and single quotes (39). If 's' matches either of these
 * values, the function returns 1. Otherwise, it returns 0.
 *
 * @param s The character to check.
 * @return  Returns 1 if 's' represents the end of quotes, 0 otherwise.
 */

int	endofquotes(char s)
{
	if (s == 34)
		return (1);
	else if (s == 39)
		return (1);
	return (0);
}

/**
 * Determines if the given lexer node 'node' has a type that matches the character 's'. It checks
 * the 'type' value of the node against specific type values for the nodes
 *  and returns 1 if there is a match. Otherwise, it returns 0.
 *
 * @param node The lexer node to check.
 * @param s    The character to match against the node's type.
 * @return     Returns 1 if the node's type matches 's', 0 otherwise.
 */

int	node_type(t_lexer *node, char s)
{
	if (node->type == red_in)
		return (1);
	else if (node->type == red_out)
		return (1);
	else if (node->type == here_doc)
		return (1);
	else if (node->type == app_out)
		return (1);
	if (s == '|')
		if (node->type == pipem)
			return (1);
	return (0);
}
