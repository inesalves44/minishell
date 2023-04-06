/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/05 00:13:33 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_file(t_ast *node, int *fd)
{
	int		fd1;
	char	*buf;

	if (node->prev && node->prev->type == red_in)
		fd1 = open(node->file, O_RDONLY);
	else
		fd1 = open(".here_doc", O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (fd1 < 0)
		return (error_process("no such file or directory: ", node, 1));
	if (node->prev->type == here_doc)
	{
		while (1)
		{
			write(1, ">", 1);
			buf = get_next_line(0);
			write(fd1, buf, ft_strlen(buf));
			if (ft_strlen(buf) == (ft_strlen(node->file) + 1) && \
				!ft_strncmp(buf, node->file, ft_strlen(node->file)))
				break ;
			free(buf);
		}
		fd1 = open(".here_doc", O_RDONLY);
		if (fd1 < 0)
			return (error_process("no such file or directory: ", node, 1));
	}
	*fd = fd1;
	return (0);
}

int	output_file(t_ast *node, int *fd)
{
	int fd1;

	if (node->prev->type == red_out)
		fd1 = open(node->file, O_CREAT | O_TRUNC | O_RDWR, 0000666);
	else
		fd1 = open(node->file, O_APPEND | O_CREAT | O_RDWR, 0000666);
	if (fd1 < 0)
		return (error_process("no such file or directory: ", node, 1));
	*fd = fd1;
	return (0);
}

void	checking_next_node(t_ast **tree)
{
	while ((*tree)->prev)
		*tree = (*tree)->prev;
	while ((*tree)->type == red_in || (*tree)->type == red_out || (*tree)->type == app_out || (*tree)->type == here_doc)
		(*tree) = (*tree)->rigth;
}

int	checking_processes(t_root *root)
{
	int pid;
	int status;

	status = 0;
	if (!counting_pipes(root->tree))
	{
		while (tree)
		{
			if (tree->type == red_in || tree->type == here_doc)
				status = input_file(tree->left, &in);
			else if (tree->type == red_out || tree->type == app_out)
				status = output_file(tree->left, &out);
			else if (!tree->rigth)
				break ;
			if (status)
				return (status);
			tree = tree->rigth;
		}
		checking_next_node(&tree);
		if (tree->type == command)
		{
			pid = fork();
			if (pid == 0)
				do_command(tree, in, out, envp);
			waitpid(pid, &status, 0);
			while (tree->prev)
				tree = tree->prev;
			while (tree)
			{
				if (tree->type == here_doc)
				{
					unlink(".here_doc");
					break ;
				}
				if (!tree->rigth)
					break ;
				tree = tree->rigth;
			}
			if (tree->prev)
				while (tree->prev)
					tree = tree->prev;
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}
	else
	{
		status = doing_pipes(&tree, in, out, envp);
		return (status);
	}
	return (status);
}

/*int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	char **str;
	t_ast *tree;
	t_lexer *lexer;
	int fd_in;
	int fd_out;
	int	status;

	tree = NULL;
	lexer = NULL;
	status = 0;
	line = NULL;
	//while (1)
	//{
		if (!line)
			line = readline("\033[1;31m prompt: \033[0m");
		if (line && !ft_strncmp(line, "exit", 4))
			exit(EXIT_SUCCESS);
		if (!lexical_annalysis(&lexer, line))
		{
			if(!parsing_str(&lexer, &tree))
			{
				fd_in = 0;
				fd_out = 1;
				status = checking_processes(tree, envp, fd_in, fd_out);		
			}
			free_tree(&tree, 0);
		}
		if (lexer)
			free_lexer(&lexer);
		fd_in = 0;
		fd_out = 1;
		status = checking_processes(tree, envp, fd_in, fd_out);
		if (tree)
			free_tree(tree, 0);
		add_history(line);
		free(line);
		line = NULL;
	//}
	return (0);
}*/
