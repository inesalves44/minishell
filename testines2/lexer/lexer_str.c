/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:03:32 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/25 20:08:41 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_string3(char *line, int *i, int len)
{
	char	*aux;
	char	*str;
	char	s;

	str = NULL;
	aux = NULL;
	str = start_str(line, i, len);
	if (*i == len)
		return (str);
	s = line[*i];
	aux = aux_quotes(line, i, len, s);
	str = complete_strlexer(str, aux);
	free(aux);
	if (*i == len)
		return (str);
	s = change_q(s);
	str = mid_str(line, i, str, len);
	if (*i == len)
		return (str);
	s = line[*i];
	aux = aux_quotes(line, i, len, s);
	str = complete_strlexer(str, aux);
	free(aux);
	return (str);
}

char	*treat_begin(char *line, int len)
{
	int		i;
	int		len1;
	char	*str;

	i = 0;
	len1 = len - 1;
	while (line[i] == 34 || line[i] == 39)
		i++;
	while (line[len1] != 34 && line[len1] != 39)
		len1--;
	if (len1 + 1 == i)
	{
		str = ft_substr(line, i, len);
		return (str);
	}
	return (NULL);
}

char	*treat_end(char *line, int len, int i)
{
	int		a;
	char	*str;

	a = i;
	str = NULL;
	while (line[i] == 34 || line[i] == 39)
		i++;
	if (i == len && i > a)
		str = ft_strdup(&line[a]);
	return (str);
}

char	*create_string2(char *line, int len)
{
	int		i;
	char	*str;
	char	*aux;

	i = 0;
	aux = NULL;
	str = NULL;
	while (line[i] != 34 && line[i] != 39 && i < len)
		i++;
	if (i == len)
	{
		str = ft_strdup(line);
		return (str);
	}
	if (i > 0)
		aux = ft_substr(line, 0, i);
	str = treat_begin(line, len);
	str = treat_end(line, len, i);
	if (!str)
		str = create_string3(line, &i, len);
	if (aux)
		str = lexer_strjoin(aux, str);
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
