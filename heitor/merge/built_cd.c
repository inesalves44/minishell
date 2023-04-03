/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:11:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/02 21:59:35 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*transform(char cwd[])
{
	char	*path;
	int		i;

	i = 0;
	path = ft_calloc(sizeof(char), ft_strlen(cwd) + 1);
	while(cwd[i])
	{
		path[i] = cwd[i];
		i++;
	}
	return (path);
}

void	cd(t_root *root)
{
	int		size;
	char	*err;
	char	*path;
	char cwd[BUFFER_PATH];

	size = get_array_size(root->ast_tree.command);
	if(size == 1)
	{
		path = get_env_value(root, "HOME");
		chdir(path);
		change_value(root, "PWD", path);
	}
	else if (size > 2)
		printf("minishell: cd: too many arguments\n");
	else
	{
		err = ft_strjoin("minishell: cd: ", root->ast_tree.command[1]);
		if (chdir(root->ast_tree.command[1]) == 0)
		{
			getcwd(cwd, BUFFER_PATH);
			change_value(root, "PWD", transform(cwd));
		}
		else
			perror(err);
		free(err);
	}
}
