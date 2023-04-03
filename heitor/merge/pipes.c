/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:25:07 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/03 11:46:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int counting_pipes(t_ast *tree)
{
	int	pipes;

	pipes = 0;
	while (tree->rigth)
	{
		if (tree->type == pipem)
			pipes++;
		tree = tree->rigth;
	}
	while (tree->prev)
		tree = tree->prev;
	return (pipes);
}

int	*creating_pipes(t_ast *tree, int pipes)
{
	int *array;
	int	i;

	array = (int *)malloc(sizeof(int) * 2 * pipes);
	if (!array)
		return (NULL);
	i = 0;
	while (i < pipes)
	{
		if (pipe(array + (2 * i)) < 0)
			return (NULL);
		i++;
	}
	return (array);
}

int	child_in(t_ast *tree, int in, int *pipes, char *envp[])
{
	char *envp2;
	char **paths;
	char *cmd_path;

	dup2(pipes[1], 1);
	dup2(in, 0);
	close_fd(tree, pipes);
	envp2 = get_path(envp);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(tree->command[0], paths);
	if (!cmd_path)
		return (error_process(" command not found", tree, 127));
	if (execve(cmd_path, tree->command, envp) < 0)
		return (error_process("execve error", NULL, 1));
	return (0);
}

int	child_out(t_ast *tree, int out, int *pipes, char *envp[])
{
	char	*envp2;
	char	**paths;
	char	*cmd_path;

	dup2(pipes[counting_pipes(tree) * 2 - 2], 0);
	dup2(out, 1);
	close_fd(tree, pipes);
	envp2 = get_path(envp);
	paths = ft_split(envp2, ':');
	while (tree->rigth)
		tree = tree->rigth;
	cmd_path = find_path(tree->command[0], paths);
	if (!cmd_path)
		return (error_process(" command not found", tree, 127));
	if (execve(cmd_path, tree->command, envp) < 0)
		return (error_process("execve error", NULL, 1));
	return(0);
}

int	child_mid(t_ast *tree, int *pipes, int i, char *envp[])
{
	char	*envp2;
	char	**paths;
	char	*cmd_path;
	int		j;

	dup2(pipes[2 * i - 2], 0);
	dup2(pipes[2 * i + 1], 1);
	close_fd(tree, pipes);
	envp2 = get_path(envp);
	paths = ft_split(envp2, ':');
	j = 0;
	while (j < i)
	{
		tree = tree->rigth;
		j++;
	}
	cmd_path = find_path(tree->left->command[0], paths);
	if (!cmd_path)
		return (error_process(" command not found", tree, 127));
	if (execve(cmd_path, tree->left->command, envp) < 0)
		return (error_process("execve error", NULL, 1));
	return (0);
}

int	doing_pipes(t_ast *tree, int in, int out, char *envp[])
{
	int		*pipes;
	int		num_pipes;
	int 	status;
	int		i;
	pid_t	pid;


	i = 0;
	num_pipes = counting_pipes(tree);
	pipes = creating_pipes(tree, num_pipes);
	while (i < num_pipes * 2)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				child_in((tree)->left, in, pipes, envp);
			else if (i == num_pipes * 2 - 1)
				child_out(tree, out, pipes, envp);
			else
				child_mid(tree, pipes, i, envp);
		}
		i++;
	}

	close_fd(tree, pipes);
	waitpid(-1, &status, 0);
	return (0);
}
