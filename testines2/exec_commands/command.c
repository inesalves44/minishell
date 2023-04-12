/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:45:50 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/08 00:04:10 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	do_command(t_root *root)
{
	char **paths;
	char *envp2;
	char *cmd_path;

	dup2(root->in, 0);
	dup2(root->out, 1);
	envp2 = get_path(root->env_array);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(root->tree->command[0], paths);
	free_array(paths);
	if (!cmd_path)
		return (error_process(":command not found", root->tree, 127));
	if (execve(cmd_path, root->tree->command, root->env_array) < 0)
	{
		free(cmd_path);
		return (error_process("execve error", NULL, 1));
	}
	return (0);
}