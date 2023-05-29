/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:47:21 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/29 10:40:33 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Extracts a substring from the 'line' starting from index '*i' until the first occurrence
 * of a single or double quote (34 or 39) or until reaching 'len'.
 * Returns the extracted substring or NULL if no quote is found.
 *
 * @param line The input line to extract the substring from.
 * @param i    A pointer to the current index in the line.
 * @param len  The length of the line.
 * @return     Returns the extracted substring or NULL if no quote is found.
 */

char	*start_str(char *line, int *i, int len)
{
	int		a;
	char	*str;

	a = *i;
	str = NULL;
	while (line[*i] != 34 && line[*i] != 39 && *i < len)
		(*i)++;
	if (a == *i)
		return (NULL);
	if (a < *i)
		str = ft_substr(line, a, *i - a);
	if (*i == len)
		if (!str)
			str = ft_strdup(line);
	return (str);
}

/**
 * Swaps the given character 's' between single and double quotes (34 and 39).
 *
 * @param s The character to swap quotes for.
 * @return  Returns the character with swapped quotes.
 */

char	change_q(char s)
{
	if (s == 34)
		s = 39;
	else if (s == 39)
		s = 34;
	return (s);
}

/**
 * Extracts a substring from the 'line' starting from index '*i' until the first occurrence
 * of a single or double quote (34 or 39) or until reaching 'len'.
 * Concatenates the extracted substring 'aux' with the given 'str'.
 *
 * @param line The input line to extract the substring from.
 * @param i    A pointer to the current index in the line.
 * @param str  The string to concatenate with the extracted substring.
 * @param len  The length of the line.
 * @return     Returns the resulting string after concatenation.
 */

char	*mid_str(char *line, int *i, char *str, int len)
{
	int		a;
	char	*aux;
	char	*str1;
	char	*str2;

	aux = NULL;
	a = *i;
	str1 = NULL;
	str2 = NULL;
	while (line[*i] != 34 && line[*i] != 39 && *i < len)
		(*i)++;
	if (a < *i)
	{
		str2 = ft_strdup(str);
		aux = ft_substr(line, a, *i - a);
		if (str2 && aux)
			str1 = ft_strjoin(str2, aux);
		else if (!str2 && aux)
			str1 = ft_strdup(aux);
		free(aux);
		free(str2);
	}
	return (str1);
}

/**
 * Concatenates the given strings 'str' and 'aux' using 'ft_strjoin' function.
 * If either 'str' or 'aux' is NULL, duplicates the non-NULL string using 'ft_strdup'.
 *
 * @param str The first string to concatenate.
 * @param aux The second string to concatenate.
 * @return    Returns the resulting concatenated or duplicated string.
 */

char	*complete_strlexer(char *str, char *aux)
{
	char	*str2;

	str2 = NULL;
	if (str && aux)
		str2 = ft_strjoin(str, aux);
	else if (!str && aux)
		str2 = ft_strdup(aux);
	else if (str && !aux)
		str2 = ft_strdup(str);
	return (str2);
}

/**
 * Counts the number of non-space characters in the given string 'aux'.
 * Auxiliary function!
 *
 * @param aux The input string to count non-space characters.
 * @return    Returns the count of non-space characters.
 */

int	aux_space(char *aux)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (aux[i] != '\0')
	{
		if (aux[i] != ' ')
			a++;
		i++;
	}
	return (a);
}
