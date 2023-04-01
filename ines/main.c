/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/01 13:18:45 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_file(t_ast *node)
{
	int fd;

	fd = open(node->file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

int	output_file(t_ast *node)
{
	int fd;

	fd = open(node->file, O_TRUNC | O_CREAT | O_RDWR, 0000666);
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

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

void close_fd(t_ast *tree, int *pipes)
{
	int num_pipes;
	int	i;

	num_pipes = counting_pipes(tree);
	i = 0;
	while (i < num_pipes * 2)
	{
		close(pipes[i]);
		i++;
	}
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
		exit(EXIT_FAILURE);
	if (execve(cmd_path, tree->command, envp) < 0)
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	if (execve(cmd_path, tree->command, envp) < 0)
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	if (execve(cmd_path, tree->left->command, envp) < 0)
		exit(EXIT_FAILURE);
	return (0);
}

int	doing_pipes(t_ast **tree, int in, int out, char *envp[])
{
	int		*pipes;
	int		num_pipes;
	int 	status;
	int		i;
	pid_t	pid;

	i = 0;
	num_pipes = counting_pipes(*tree);
	if (num_pipes == 1)
		num_pipes++;
	pipes = creating_pipes(*tree, num_pipes);
	while (i < num_pipes * 2 - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				child_in((*tree)->left, in, pipes, envp);
			else if (i == num_pipes * 2 - 2)
				child_out((*tree), out, pipes, envp);
			else
				child_mid((*tree), pipes, i, envp);
		}
		i++;
	}
	close_fd(*tree, pipes);
	wait(NULL);
	*tree = (*tree)->rigth;
	while ((*tree)->rigth && (*tree)->rigth->type == pipem)
		*tree = (*tree)->rigth;
	return (0);
}

int	checking_processes(t_ast *tree, char *envp[], int in, int out)
{
	int pid;
	int status;

	if (tree->type == red_in)
	{
		in = input_file(tree->left);
		free (tree->left);
		tree->left = NULL;
	}
	else if (tree->type == red_out)
	{
		out = output_file(tree->left);
		free (tree->left);
		tree->left = NULL;
	}
	else if (tree->type == pipem)
	{
		status = doing_pipes(&tree, in, out, envp);
		return (status);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			do_command(tree, in, out, envp);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	if (tree->rigth && tree->rigth->type != pipem)
		status = checking_processes(tree->rigth, envp, in, out);
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	char **str;
	t_ast *tree;
	int fd_in;
	int fd_out;

	tree = NULL;
	while (1)
	{
		line = readline("\033[1;31m prompt: \033[0m");
		str = ft_split(line,' ');
		if (str && !ft_strncmp(str[0], "exit", 4))
			exit(EXIT_SUCCESS);
		tree = parsing_str(str);
		fd_in = 0;
		fd_out = 1;
		checking_processes(tree, envp, fd_in, fd_out);
		add_history(line);
	}
	return (0);
}
