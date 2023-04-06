/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:11:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/05 08:25:36 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_pwd()
{
	char cwd[BUFFER_PATH];

	getcwd(cwd, BUFFER_PATH);
	return (transform(cwd));
}

void	cd(t_root *root)
{
	char	*err;
	char	*path;

	path = NULL;
	if(get_array_size(root->tree->command) == 1)
	{
		path = get_env_value(root, "HOME");
		chdir(path);
		change_value(root, "PWD", path);
	}
	else if (get_array_size(root->tree->command) > 2)
		printf("minishell: cd: too many arguments\n");
	else
	{
		err = ft_strjoin("minishell: cd: ", root->tree->command[1]);
		if (chdir(root->tree->command[1]) == 0)
		{
			path = get_pwd();
			change_value(root, "PWD", path); //already changes the list;
		}
		else
			perror(err);
		free(err);
	}
	if (path)
		free(path);
}
