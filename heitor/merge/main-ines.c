/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-ines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/03 10:40:39 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_file(t_ast *node, int *fd)
{
	int fd1;

	fd1 = open(node->file, O_RDONLY);
	if (fd1 < 0)
		return (error_process("no such file or directory: ", node, 1));
	*fd = fd1;
	return (0);
}

int	output_file(t_ast *node, int *fd)
{
	int fd1;

	fd1 = open(node->file, O_CREAT | O_TRUNC | O_RDWR, 0000666);
	if (fd1 < 0)
		return (error_process("no such file or directory: ", node, 1));
	*fd = fd1;
	return (0);
}

void	checking_next_node(t_ast **tree)
{
	while ((*tree)->prev)
		*tree = (*tree)->prev;
	while ((*tree)->type == red_in || (*tree)->type == red_out)
		(*tree) = (*tree)->rigth;
}

int	checking_processes(t_ast *tree, char *envp[], int in, int out)
{
	int pid;
	int status;

	status = 0;
	while (tree)
	{
		if (tree->type == red_in)
			status = input_file(tree->left, &in);
		else if (tree->type == red_out)
			status = output_file(tree->left, &out);
		else if (!tree->rigth)
			break ;
		if (status)
			return (status);
		tree = tree->rigth;
	}
	checking_next_node(&tree);
	if (tree->type == pipem)
	{
		status = doing_pipes(&tree, in, out, envp);
		return (status);
	}
	else if (tree->type == command)
	{
		pid = fork();
		if (pid == 0)
			do_command(tree, in, out, envp);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	char **str;
	t_ast *tree;
	int fd_in;
	int fd_out;
	int	status;

	tree = NULL;
	status = 0;
	line = NULL;
	while (1)
	{
		if (!line)
			line = readline("\033[1;31m prompt: \033[0m");
		if (line && !ft_strncmp(line, "exit", 4))
			exit(EXIT_SUCCESS);
		str = ft_split(line,' ');
		tree = parsing_str(str);
		fd_in = 0;
		fd_out = 1;
		if (tree)
		{
			status = checking_processes(tree, envp, fd_in, fd_out);
			free_tree(tree, 0);
		}
		add_history(line);
		free(line);
		line = NULL;
	}
	return (0);
}
