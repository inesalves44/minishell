/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incomp_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:34:38 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/28 18:35:51 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*complete_str(void)
{
	int		i;
	char	*str;

	i = 0;
	while (1)
	{
		write(1, ">", 1);
		str = get_next_line(0);
		if (!str)
			return (NULL);
		while (str[i] == ' ')
			i++;
		if (str[i] != '\n')
			return (str);
	}
	return (NULL);
}

char	*create_completepipe(t_ast *tree, int *i)
{
	char	*str;
	char	*new;

	str = NULL;
	new = NULL;
	*i = 0;
	while (1)
	{
		if (tree->type == pipem)
		{
			if (!tree->rigth)
			{
				str = complete_str();
				*i = 1;
				if (!str)
					return (NULL);
				break ;
			}
		}
		if (!tree->rigth)
			return (NULL);
		tree = tree->rigth;
	}
	new = ft_substr(str, 0, ft_strlen(str) - 1);
	free(str);
	return (new);
}

t_ast	*checking_unfinishpipes(t_ast *tree)
{
	char	*new;
	t_lexer	*node;
	t_ast	*aux;
	int		i;

	aux = NULL;
	new = create_completepipe(tree, &i);
	if (!new && i == 1)
		return (NULL);
	else if (!new && i == 0)
		return (tree);
	lexical_annalysis(&node, new);
	parsing_str(&node, &aux);
	tree->rigth = aux;
	aux->prev = tree;
	while (tree->prev)
		tree = tree->prev;
	free(new);
	return (tree);
}
