/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:03:32 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/25 11:12:05 by idias-al         ###   ########.fr       */
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

char	*add_quotes(char s, char *aux)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = s;
	str[1] = '\0';
	aux = ft_strjoin(str, aux);
	aux = ft_strjoin(aux, str);
	free(str);
	return (aux);
}

char	*create_string3(char *line, int *i, int len, int c)
{
	int		a;
	char	*aux;
	char	*str;
	char	s;

	str = NULL;
	aux = NULL;
	a = *i;
	while (line[*i] != 34 && line[*i] != 39 && *i < len)
		(*i)++;
	if (a < *i)
		str = ft_substr(line, a, *i - a);
	s = line[*i];
	if (*i == len)
	{
		if (!str)
			str = ft_strdup(line);
		return (str);
	}
	if (closing_q2(line, line[*i], *i, len))
	{
		aux = find_string(line, i, len);
		if (aux && aux[0] == s)
		{
			c = 1;
			aux = create_string3(aux, &c, ft_strlen(aux) - 1, c);
			if (aux)
				aux = add_quotes(s, aux);
		}
		else if (aux && aux[0] != s)
		{
			c = 0;
			aux = create_string3(aux, &c, ft_strlen(aux), c);
		}
	}
	else
	{
		a = *i;
		(*i)++;
		while (line[*i] != 34 && line[*i] != 39 && *i < len)
			(*i)++;
		aux = ft_substr(line, a, *i - a);
	}
	if (str && aux)
		str = ft_strjoin(str, aux);
	else if (!str && aux)
		str = ft_strdup(aux);
	free(aux);
	if (*i == len)
		return (str);
	if (s == 34)
		s = 39;
	else if (s == 39)
		s = 34;
	a = *i;
	while (line[*i] != 34 && line[*i] != 39 && *i < len)
		(*i)++;
	if (a < *i)
		str = ft_strjoin(str ,ft_substr(line, a, *i - a));
	s = line[*i];
	if (*i == len)
		return (str);
	if (closing_q2(line, line[*i], *i, len))
	{
		aux = find_string(line, i, len);
		if (aux && aux[0] == s)
		{
			c = 1;
			aux = create_string3(aux, &c, ft_strlen(aux) - 1, c);
			if (aux)
				aux = add_quotes(s, aux);
		}
		else if (aux && aux[0] != s)
		{
			c = 0;
			aux = create_string3(aux, &c, ft_strlen(aux), c);
		}
	}
	else
	{
		a = *i;
		(*i)++;
		while (line[*i] != 34 && line[*i] != 39 && *i < len)
			(*i)++;
		aux = ft_substr(line, a, *i - a);
	}
	if (str && aux)
		str = ft_strjoin(str, aux);
	else if (!str && aux)
		str = ft_strdup(aux);
	free(aux);
	return(str);
}

char	*create_string2(char *line, int len)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != 34 && line[i] != 39 && i == len)
		i++;
	if (i == len)
	{
		str = ft_strdup(line);
		return (str);
	}
	str = create_string3(line, &i, len, 0);
	return (str);
}

char	*create_string(char *line)
{
	int		len;
	int		a;
	int		i;
	char	*str;

	if (line[0] == '\0')
		return (NULL);
	len = ft_strlen(line);
	a = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 34 || line[i] == 39)
			a++;
		i++;
	}
	if (a == len)
	{
		write(2, "syntax error\n", 13);
		return (NULL);
	}
	str = create_string2(line, len);
	return (str);
}