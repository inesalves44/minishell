/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:53:08 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/03 14:57:54 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (str2);
}

char	*final_aux(char *line, char *aux, int len, int *i)
{
	char	*str;
	char	*str1;

	str = NULL;
	str = treat_begin(line, len);
	str = treat_end(line, len, *i);
	if (!str)
		str = create_string3(line, i, len);
	if (aux)
		str1 = ft_strjoin(aux, str);
	else
		str1 = ft_strdup(str);
	if (str)
		free(str);
	return (str1);
}