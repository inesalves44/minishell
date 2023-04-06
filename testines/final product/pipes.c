/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:25:07 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/05 00:33:59 by idias-al         ###   ########.fr       */
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

	(void)tree;
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

int	child_in(t_ast *tree, int in, int out, int *pipes, char *envp[])
{
	char *envp2;
	char **paths;
	char *cmd_path;

	dup2(out, 1);
	dup2(in, 0);
	close_fd(tree, pipes);
	envp2 = get_path(envp);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(tree->left->command[0], paths);
	if (!cmd_path)
		return (error_process(" command not found", tree, 127));
	if (execve(cmd_path, tree->left->command, envp) < 0)
		return (error_process("execve error", NULL, 1));
	return (0);
}

int	child_out(t_ast *tree, int in, int out, int *pipes, char *envp[])
{
	char	*envp2;
	char	**paths;
	char	*cmd_path;

	dup2(in, 0); 
	dup2(out, 1);
	close_fd(tree, pipes);
	envp2 = get_path(envp);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(tree->command[0], paths);
	if (!cmd_path)
		return (error_process(" command not found", tree, 127));
	if (execve(cmd_path, tree->command, envp) < 0)
		return (error_process("execve error", NULL, 1));
	return(0);
}

int	child_mid(t_ast *tree, int in, int out, int *pipes, char *envp[])
{
	char	*envp2;
	char	**paths;
	char	*cmd_path;

	dup2(in, 0);
	dup2(out, 1);
	close_fd(tree, pipes);
	envp2 = get_path(envp);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(tree->left->command[0], paths);
	if (!cmd_path)
		return (error_process(" command not found", tree, 127));
	if (execve(cmd_path, tree->left->command, envp) < 0)
		return (error_process("execve error", NULL, 1));
	return (0);
}

int	checking_redirects(t_ast **tree, int i, int *in, int *out, int *pipes, int num_pipes, int max)
{
	int	in2;
	int	out2;
	int	status;

	in2 = 0;
	out2 = 0;
	while (*tree)
	{
		if ((*tree)->type == red_in || (*tree)->type == here_doc)
		{
			status = input_file((*tree)->left, in);
			if (status)
				return (status);
		}
		else if ((*tree)->type == red_out || (*tree)->type == app_out)
		{
			status = output_file((*tree)->left, out);
			if (status)
				return (status);
		}
		else if ((*tree)->type == pipem || (*tree)->type == command)
			break ;
		*tree = (*tree)->rigth;
	}

	if (*in == 0)
	{
		if (i == 0)
			in2 = 0;
		else if (i == max - 1)
			in2 = pipes[num_pipes * 2 - 2];
		else
			in2 = pipes[2 * i - 2];
		*in = in2;
	}
	if (*out == 1)
	{
		if (i == 0)
			out2 = pipes[1];
		else if (i == max -1)
			out2 = 1;
		else
			out2 = pipes[2 * i + 1];
		*out = out2;	
	}
	return (0);
}

int	doing_pipes(t_ast **tree, int in, int out, char *envp[])
{
	int		*pipes;
	int		num_pipes;
	int 	status;
	int		i;
	int		max;
	pid_t	pid;


	i = 0;
	num_pipes = counting_pipes(*tree);
	pipes = creating_pipes(*tree, num_pipes);
	max = num_pipes + 1;
	while (i < max)
	{
		in = 0;
		out = 1;
		checking_redirects(tree, i,  &in, &out, pipes, num_pipes, max);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				child_in((*tree), in, out, pipes, envp);
			else if (i == max - 1)
				child_out((*tree), in, out, pipes, envp);
			else
				child_mid((*tree), in, out, pipes, envp);
		}
		if ((*tree)->rigth)
			*tree = (*tree)->rigth;
		i++;
	}
	close_fd(*tree, pipes);
	waitpid(-1, &status, 0);
	return (0);
}