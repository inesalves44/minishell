/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:25:07 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/13 17:53:08 by idias-al         ###   ########.fr       */
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
	cmd_path = find_path(root->tree->left->command[0], paths);
	free_array(paths);
	if (!cmd_path)
		exit (error_process(" command not found", root->tree->left, 127));
	if (execve(cmd_path, root->tree->left->command, root->env_array) < 0)
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
	cmd_path = find_path(root->tree->rigth->command[0], paths);
	free_array(paths);
	if (!cmd_path)
		exit (error_process(" command not found", root->tree->rigth, 127));
	if (execve(cmd_path, root->tree->rigth->command, root->env_array) < 0)
	{
		free(cmd_path);
		exit (error_process("execve error", NULL, 1));
	}
	exit (0);
}

/*int	child_mid(t_root *root)
{
	char	*envp2;
	char	**paths;
	char	*cmd_path;

	dup2(root->in, 0);
	dup2(root->out, 1);
	close_fd(root->tree, root->pipes);
	envp2 = get_path(root->env_array);
	paths = ft_split(envp2, ':');
	cmd_path = find_path(root->tree->left->command[0], paths);
	free_array(paths);
	if (!cmd_path)
		exit (error_process(" command not found", root->tree->left, 127));
	if (execve(cmd_path, root->tree->left->command, root->env_array) < 0)
	{
		free(cmd_path);
		exit (error_process("execve error", NULL, 1));
	}
	exit (0);
}
*/
int	checking_redirects(t_root *root, int i, int max)
{
	int	in2;
	int	out2;

	in2 = 0;
	out2 = 0;
	while (root->tree)
	{
		if (root->tree->type == red_in || root->tree->type == here_doc)
			root->status = input_file(root);
		else if (root->tree->type == red_out || root->tree->type == app_out)
			root->status = output_file(root);
		else if (root->tree->type == pipem || root->tree->type == command)
			break ;
		if (!root->tree->rigth)
			break ;
		root->tree = root->tree->rigth;
	}
	if (root->status)
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
	if (root->status)
		return (root->status);
	return (0);
}

t_ast	*checking_unfinishpipes(t_ast *tree)
{
	char	*str;
	t_lexer	*node;
	t_ast	*aux;

	str = NULL;
	aux = NULL;
	while (1)
	{
		if (tree->type == pipem)
		{
			if (!tree->rigth)
			{
				write(1, ">", 1);
				str = get_next_line(0);
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
	lexical_annalysis(&node, str);
	parsing_str(&node, &aux);
	tree->rigth = aux;
	while (tree->prev)
		tree = tree->prev;
	return (tree);
}

int	doing_pipes(t_root *root)
{
	int 	status;
	int		i;
	pid_t	pid;

	root->tree = checking_unfinishpipes(root->tree);
	i = 0;
	root->num_pipes = counting_pipes(root->tree);
	root->pipes = creating_pipes(root->tree, root->num_pipes);
	root->isbuilt = 0;
	pid = 0;
	while (i < root->num_pipes)
	{
		root->in = 0;
		root->out = 1;
		if (!checking_redirects(root, i, root->num_pipes + 1))
		{
			if (i != root->num_pipes)
				root->tree = root->tree->left;
			if (root->tree->type == pipem)
				root->tree = root->tree->rigth;
			if (root->tree->command && ft_strncmp("cd", root->tree->command[0], 2) && is_built(root->tree->command))
			{
				root->isbuilt = open(".temp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
				root->out = root->isbuilt;
				built_in_router(root);
			}
			else if (root->tree->command && !is_built(root->tree->command))
			{
				if (fork() == 0)
				{
					root->tree = root->tree->prev;
					child_in(root);
				}	
			}
		}
		root->tree = root->tree->prev;
		if (root->tree->rigth)
			root->tree = root->tree->rigth;
		i++;
	}
	root->in = 0;
	root->out = 1;
	if (!checking_redirects(root, i, root->num_pipes + 1))
	{
		//root->tree = root->tree->rigth;
		if (root->tree->command && ft_strncmp("cd", root->tree->command[0], 2) && is_built(root->tree->command))
		{
			root->isbuilt = open(".temp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
			root->out = root->isbuilt;
			built_in_router(root);
		}
		else if (root->tree->command && !is_built(root->tree->command))
		{
			pid = fork();
			printf("%d\n", pid);
			if (pid == 0)
			{
				printf("helloooooo!!!!!");
				root->tree = root->tree->prev;
				child_out(root);
			}
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
		if (root->tree->type == command && is_built(root->tree->command))
			unlink(".temp");
		else if (root->tree->left && root->tree->left->type == command && is_built(root->tree->left->command))
			unlink(".temp");
		if (!root->tree->rigth)
			break;
		root->tree = root->tree->rigth;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}