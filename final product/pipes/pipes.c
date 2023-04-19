/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:25:07 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/19 13:09:32 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int counting_pipes(t_ast *tree)
{
	int	pipes;

	pipes = 0;
	while (tree)
	{
		if (tree->type == pipem)
			pipes++;
		if (!tree->rigth)
			break ;
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

int	child_in(t_root *root)
{
	char *envp2;
	char **paths;
	char *cmd_path;

	dup2(root->in, 0);
	dup2(root->out, 1);
	close_fd(root->tree, root->pipes);
	envp2 = get_path(root->env_array);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(root->tree->command[0], paths);
	free_array(paths);
	if (!cmd_path)
		exit (error_process(" command not found", root->tree, 127));
	if (execve(cmd_path, root->tree->command, root->env_array) < 0)
	{
		free(cmd_path);
		exit (error_process("execve error", NULL, 1));
	}
	exit (0);
}

int	child_out(t_root *root)
{
	char	*envp2;
	char	**paths;
	char	*cmd_path;

	dup2(root->in, 0);
	dup2(root->out, 1);
	close_fd(root->tree, root->pipes);
	envp2 = get_path(root->env_array);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(root->tree->command[0], paths);
	free_array(paths);
	if (!cmd_path)
		exit (error_process(" command not found", root->tree, 127));
	if (execve(cmd_path, root->tree->command, root->env_array) < 0)
	{
		free(cmd_path);
		exit (error_process("execve error", NULL, 1));
	}
	exit (0);
}

int	checking_redirects_pipes(t_root *root, int i, int max)
{
	int	in2;
	int	out2;

	in2 = 0;
	out2 = 0;
	if (checking_redirects(root, &(root->status)))
		return (root->status);
	if (root->in == 0)
	{
		if (i == 0)
			in2 = 0;
		else if (i == max - 1)
			in2 = root->pipes[root->num_pipes * 2 - 2];
		else
			in2 = root->pipes[2 * i - 2];
		root->in = in2;
	}
	if (root->isbuilt != 0)
	{
		close(root->isbuilt);
		root->in = open(".temp", O_RDONLY);
		root->isbuilt = 0;
	}
	if (root->out == 1)
	{
		if (i == 0)
			out2 = root->pipes[1];
		else if (i == max -1)
			out2 = 1;
		else
			out2 = root->pipes[2 * i + 1];
		root->out = out2;	
	}
	return (0);
}

t_ast	*checking_unfinishpipes(t_ast *tree)
{
	char	*str;
	char	*new;
	t_lexer	*node;
	t_ast	*aux;
	int		i;

	str = NULL;
	aux = NULL;
	i = 0;
	while (1)
	{
		if (tree->type == pipem)
		{
			if (!tree->rigth)
			{
				while (1)
				{
					write(1, ">", 1);
					str = get_next_line(0);
					if (!str)
						return (NULL);
					while (str[i] == ' ')
						i++;
					if (str[i] != '\n')
						break ;				
				}
				break ;
			}
		}
		if (!tree->rigth)
		{
			while (tree->prev)
				tree = tree->prev;
			return (tree);
		}
		tree = tree->rigth;
	}
	new = ft_substr(str, 0, ft_strlen(str) - 1);
	lexical_annalysis(&node, new);
	parsing_str(&node, &aux);
	tree->rigth = aux;
	aux->prev = tree;
	while (tree->prev)
		tree = tree->prev;
	free(str);
	free(new);
	return (tree);
}

int	doing_pipes(t_root *root)
{
	int 	status;
	int		i;
	pid_t	pid;

	root->tree = checking_unfinishpipes(root->tree);
	if (root->tree == NULL)
		return (130);
	i = 0;
	root->num_pipes = counting_pipes(root->tree);
	root->pipes = creating_pipes(root->tree, root->num_pipes);
	root->isbuilt = 0;
	pid = 0;
	while (i < root->num_pipes)
	{
		root->in = 0;
		root->out = 1;
		if (!checking_redirects_pipes(root, i, root->num_pipes + 1))
		{
			if (i != root->num_pipes)
				root->tree = root->tree->left;
			if (root->tree->type == pipem)
				root->tree = root->tree->rigth;
			if (root->tree->command[0] != NULL && is_built(root->tree->command, 1))
			{
				if ((root->out == root->pipes[2 * i + 1] && i > 0) || (root->out == root->pipes[1] && i == 0))
				{
					root->isbuilt = open(".temp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
					root->out = root->isbuilt;	
				}
				built_in_router(root);
			}
			else if (root->tree->command[0] != NULL && !is_built(root->tree->command, 0))
				if (fork() == 0)
					child_in(root);
		}
		root->tree = root->tree->prev;
		if (root->tree->rigth)
			root->tree = root->tree->rigth;
		i++;
	}
	root->in = 0;
	root->out = 1;
	if (!checking_redirects_pipes(root, i, root->num_pipes + 1))
	{
		if (root->tree->command[0] != NULL && is_built(root->tree->command, 1))
			built_in_router(root);
		else if (root->tree->command[0] != NULL && !is_built(root->tree->command, 0))
		{
			pid = fork();
			if (pid == 0)
				child_out(root);
		}	
	}
	close_fd(root->tree, root->pipes);
	waitpid(pid, &status, 0);
	while (i-- >= 0)
		waitpid(0, NULL, 0);
	while (root->tree->prev)
		root->tree = root->tree->prev;
	while (root->tree)
	{
		if (root->tree->type == here_doc)
			unlink(".here_doc");
		if (root->tree->type == command && is_built(root->tree->command, 0))
			unlink(".temp");
		else if (root->tree->left && root->tree->left->type == command && is_built(root->tree->left->command, 0))
			unlink(".temp");
		if (!root->tree->rigth)
			break ;
		root->tree = root->tree->rigth;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}