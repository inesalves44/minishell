/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:03:32 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/20 19:17:19 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*find_string(char *line, int *i, int len)
{
	char	s;
	int		len1;
	int		test;
	char	*aux;
	int		b;

	b = 1;
	s = line[*i];
	len1 = len - 1;
	while (line[len1] != s)
		len1--;
	test = len1;
	while (line[len1] == line[len1 - 1] && line[*i] == line[*i + 1])
	{
		len1--;
		(*i)++;
		b++;
	}
	if (b % 2 == 0)
	{
		(*i)++;
		len1--;
	}
	aux = ft_substr(line, *i, len1 - *i + 1);
	*i = test + 1;
	return (aux);
}

char	*annalysing_quotes(char *line, int *i, int len)
{
	char	*aux;
	char	*str;
	char	s;
	int		a;
	int		b;
	int		c;

	aux = NULL;
	str = NULL;
	a = 0;
	b = *i;
	while (line[*i] != 34 && line[*i] != 39 && *i < len)
		(*i)++;
	if (line[*i] != 34 && line[*i] != 39)
		return  (line);
	s = line[*i];
	if (b != *i)
		str = ft_substr(line, a, *i - a);
	if (closing_q(line, line[*i], *i, NULL))
	{
		aux = find_string(line, i, len);
		c = 0;
		if (aux && aux[0] != s)
			aux = annalysing_quotes(aux, &c, ft_strlen(aux));
		else if (aux && aux[0] == s)
		{
			c++;
			aux = annalysing_quotes(aux, &(c), ft_strlen(aux) - 1);
		}
		if (str && aux)
		{
			aux = ft_strjoin(str, aux);
			free (str);
		}
	}
	if (str && !aux)
			aux = ft_strdup(str);
	if (line[*i] == '\0')
		return(aux);
	a = *i;
	if (s == 34)
		s = 39;
	else
		s = 34;
	while (line[*i] != s && *i < len)
		(*i)++;
	if (*i > a)
		str = ft_substr(line, a, *i - a);
	if (line[*i] == '\0')
	{
		if (str && aux)
			aux = ft_strjoin(aux, str);
		else if (!aux && str)
			aux = ft_strdup(str);
		free(str);
		return(aux);
	}
	if (closing_q(line, line[*i], *i, NULL))
	{
		if (str)
			str = ft_strjoin(aux, str);
		else
			str = ft_strdup(aux);
		if (aux)
			free(aux);
		aux = find_string(line, i, len);
		c = 0;
		if (aux && aux[0] == s)
			aux = annalysing_quotes(aux, &c, ft_strlen(aux) - 1);
		else if (aux && aux[0] != s)
		{
			c++;
			aux = annalysing_quotes(aux, &(c), ft_strlen(aux));
		}
		if (str && aux)
		{
			aux = ft_strjoin(str, aux);
			free (str);
		}
		else if (str && !aux)
			aux = ft_strdup(str);
	}
	else
	{
		a = *i;
		while (*i < len)
			(*i)++;
		aux = ft_substr(line, a, *i - a + 1);
	}
	return (aux);
}

char	*create_string(char *line)
{
	char	*str;
	char	*aux;
	int		i;
	int		len;
	int		a;

	i = 0;
	str = NULL;
	len = ft_strlen(line);
	while (line[i] != 34 && line[i] != 39 && line[i] != '\0')
		i++;
	if (line[i] == '\0')
	{
		str = ft_strdup(line);
		return (str);
	}
	if (i > 0 && !closing_q(line, line[i], i, NULL))
	{
		i++;
		while (line[i] != 34 && line[i] != 39 && line[i] != '\0')
			i++;
		str = ft_substr(line, 0, i);
		if (line[i] == '\0')
			return (str);
	}
	else if (i > 0 && closing_q(line, line[i], i, NULL))
		str = ft_substr(line, 0, i);
	aux = annalysing_quotes(line, &i, len);
	if (str && aux)
		str = ft_strjoin(str, aux);
	else if (!str && aux)
		str = ft_strdup(aux);
	else if (!aux)
	{
		a = i;
		while (line[i] != '\0')
			i++;
		str = ft_substr(line, a, i - a);
	}
	printf("%s\n", str);
	return (str);
}