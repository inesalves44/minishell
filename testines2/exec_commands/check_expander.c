/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:34:29 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/28 18:41:14 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	find_auxs(char **aux, char **aux2, t_ast **t, t_root *r)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while ((*t)->file[i] != '\0')
	{
		if ((*t)->file[i] == '$')
		{
			a = i;
			i++;
			while ((*t)->file[i] != '\0' && \
			(*t)->file[i] != '$' && (*t)->file[i] != ' ')
				i++;
			break ;
		}
		i++;
	}
	if ((*t)->file[a + 1] == '?')
		*aux = ft_strdup(ft_itoa(r->status_old));
	else
		*aux = ft_substr((*t)->file, a, i - 1);
	if (i > 0)
		*aux2 = ft_substr((*t)->file, 0, a);
}

char	*new_file(char *value, char *aux2)
{
	char	*new;

	new = NULL;
	if (aux2 && value)
		new = ft_strjoin(aux2, value);
	else if (!aux2 && value)
		new = ft_strdup(value);
	else if (!value && aux2)
		new = ft_strdup(aux2);
	return (new);
}

int	file_expander(t_ast **tree, t_root *r)
{
	char	*value;
	char	*aux;
	char	*aux2;

	value = NULL;
	aux = NULL;
	aux2 = NULL;
	find_auxs(&aux, &aux2, tree, r);
	value = get_env_value(r, aux + 1);
	if (!value && !aux2)
	{
		free(aux);
		if (aux2)
			free(aux2);
		return (e_pro(": ambiguous redirect", *tree, 1, 0));
	}
	free((*tree)->file);
	(*tree)->file = NULL;
	(*tree)->file = new_file(value, aux2);
	free(value);
	free(aux);
	if (aux2)
		free(aux2);
	return (0);
}

int	check_expander(t_root *r, t_ast **t)
{
	if ((*t)->type == file)
	{
		if ((*t)->prev->type != here_doc && check_dollar((*t)->file) \
			&& (*t)->squotes[0] == -1)
			r->status = file_expander(t, r);
	}
	else if ((*t)->type == command && (*t)->command && \
		!is_equal((*t)->command[0], "export"))
		command_expander(t, r);
	if ((*t)->left)
		check_expander(r, &(*t)->left);
	if ((*t)->rigth)
		check_expander(r, &(*t)->rigth);
	if (r->status)
		return (r->status);
	return (0);
}