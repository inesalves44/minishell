/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/28 19:54:20 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_treenode(char *str, int check, int i)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->node = i;
		node->type = check;
		if (check == 3)
			node->command = str;
		else
			node->command = NULL;
		if (check == 4)
			node->file = str;
		else
			node->file = NULL;
		node->left = NULL;
		node->rigth = NULL;
	}
	return (node);
}

void	parsing_str(char *str)
{
	t_ast	*node;
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str, "|", 1))
			i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	char **str;
	int i;

	i = 0;
	while (1)
	{
		line = readline("\033[1;31m prompt: \033[0m");
		str = ft_split(line,' ');
		parsing_str(str);
		i = 0;
		add_history(line);
	}
}
