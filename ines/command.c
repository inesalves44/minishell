/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:45:50 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/31 15:46:49 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*find_path(char *final, char **paths)
{
	char	*temp;
	char	*cmd;
	int		i;

	if (access(final, F_OK) == 0)
	{
		cmd = ft_strdup(final);
		return (cmd);
	}
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(temp, final);
		free(temp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	do_command(t_ast *tree, int in, int out, char *envp[])
{
	char **paths;
	char *envp2;
	char *cmd_path;

	dup2(in, 0);
	dup2(out, 1);
	envp2 = get_path(envp);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(tree->command[0], paths);
	if (!cmd_path)
		exit(EXIT_FAILURE);
	if (execve(cmd_path, tree->command, envp) < 0)
		exit(EXIT_FAILURE);
}