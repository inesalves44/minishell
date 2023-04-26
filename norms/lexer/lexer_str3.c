/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:47:21 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/26 18:09:52 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*start_str(char *line, int *i, int len)
{
	int		a;
	char	*str;

	a = *i;
	str = NULL;
	while (line[*i] != 34 && line[*i] != 39 && *i < len)
		(*i)++;
	if (a < *i)
		str = ft_substr(line, a, *i - a);
	if (*i == len)
		if (!str)
			str = ft_strdup(line);
	return (str);
}

char	change_q(char s)
{
	if (s == 34)
		s = 39;
	else if (s == 39)
		s = 34;
	return (s);
}

char	*mid_str(char *line, int *i, char *str, int len)
{
	int		a;

	a = *i;
	while (line[*i] != 34 && line[*i] != 39 && *i < len)
		(*i)++;
	if (a < *i)
		str = lexer_strjoin(str, ft_substr(line, a, *i - a));
	return (str);
}

char	*complete_strlexer(char *str, char *aux)
{
	if (str && aux)
		str = lexer_strjoin(str, aux);
	else if (!str && aux)
		str = ft_strdup(aux);
	return (str);
}

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
