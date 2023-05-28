/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:40:42 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/24 11:38:44 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
    Helper function: find_string2
    Updates the indices len1 and i to find the end and start positions of a repeated character sequence.
    @param line The input line to be processed.
    @param i A pointer to the current index in the line.
    @param len1 A pointer to the length of the line.
    */

void	find_string2(char *line, int *i, int *len1)
{
	int	b;

	b = 1;
	while (line[*len1] == line[*len1 - 1] && line[*i] == line[*i + 1])
	{
		(*len1)--;
		(*i)++;
		b++;
	}
	if (b % 2 == 0)
	{
		(*i)++;
		(*len1)--;
	}
}

/**

    Finds a string enclosed in quotes (single or double) starting from the current index (i) in the line.
    @param line The input line to be processed.
    @param i A pointer to the current index in the line.
    @param len The length of the input line.
    @return Returns a pointer to the found string.
    */

char	*find_string(char *line, int *i, int len)
{
	char	s;
	int		len1;
	int		test;
	char	*aux;

	s = line[*i];
	len1 = len - 1;
	while (line[len1] != s)
		len1--;
	test = len1;
	find_string2(line, i, &len1);
	if (len1 >= *i)
		aux = ft_substr(line, *i, len1 - *i + 1);
	else
		aux = ft_strdup("");
	*i = test + 1;
	return (aux);
}

/**

    Processes the found string and performs further operations based on its content and quotes.
    @param line The input line to be processed.
    @param i A pointer to the current index in the line.
    @param len The length of the input line.
    @param s The quote character.
    @return Returns a pointer to the processed string.
    */

char	*auxquotes2(char *line, int *i, int len, char s)
{
	int		c;
	char	*aux;
	char	*aux1;

	aux = find_string(line, i, len);
	aux1 = NULL;
	if (aux && aux[0] == s && aux[ft_strlen(aux) - 1] == s)
	{
		c = 1;
		aux1 = create_string3(aux, &c, ft_strlen(aux) - 1);
		if (aux1)
			aux1 = add_quotes(s, aux1);
	}
	else if (aux)
	{
		c = 0;
		aux1 = create_string3(aux, &c, ft_strlen(aux));
	}
	free(aux);
	return (aux1);
}

/**

    Processes the string enclosed in quotes, handling different cases based on its content and quotes.
    @param line The input line to be processed.
    @param i A pointer to the current index in the line.
    @param len The length of the input line.
    @param s The quote character.
    @return Returns a pointer to the processed string.
    */

char	*aux_quotes(char *line, int *i, int len, char s)
{
	char	*aux;
	int		a;

	aux = NULL;
	if (closing_q2(line, line[*i], *i, len))
		aux = auxquotes2(line, i, len, s);
	else
	{
		a = *i;
		(*i)++;
		while (line[*i] != 34 && line[*i] != 39 && *i < len)
			(*i)++;
		aux = ft_substr(line, a, *i - a);
	}
	return (aux);
}

/**

    Adds quotes around the given string that were previosly deleted to examine the string.
    @param s The quote character to add.
    @param aux The string to which the quotes should be added.
    @return Returns a pointer to the modified string with added quotes.
    */

char	*add_quotes(char s, char *aux)
{
	char	*str;
	char	*aux2;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = s;
	str[1] = '\0';
	aux2 = NULL;
	aux2 = ft_strdup(aux);
	free(aux);
	aux = NULL;
	aux = ft_strjoin(str, aux2);
	free(aux2);
	aux2 = NULL;
	aux2 = ft_strdup(aux);
	free(aux);
	aux = NULL;
	aux = ft_strjoin(aux2, str);
	free(str);
	free(aux2);
	return (aux);
}
