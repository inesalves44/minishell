/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:12:52 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/03 15:28:02 by hmaciel-         ###   ########.fr       */
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
		status = doing_pipes(tree, in, out, envp);
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

void	init_all(t_root *root, char **envp)
{
	init_envp(root, envp);
}

void	free_command(t_root *root)
{
	int	i;

	i = 0;
	while(root->tree->command[i])
	{
		free(root->tree->command[i]);
		i++;
	}
	free(root->tree->command);
}

int main(int argc, char const *argv[], char *envp[])
{
	t_root	root;
	char	*line;
	char	*prompt;
	char	**str;
	int status;
	int fd_in;
	int fd_out;

	prompt = NULL;
	status = 0;
	root.tree = NULL;

	init_all(&root, envp);


	while (1)
	{
		prompt = get_prompt(&root);
		line = readline(prompt);
    	str = ft_split(line, ' ');
		root.tree = parsing_str(str);
		fd_in = 0;
		fd_out = 1;
		if (root.tree)
		{
			status = checking_processes(root.tree, envp, fd_in, fd_out);
			free_tree(root.tree, 0);
		}

		/* if (ft_strncmp("exit", line, 4) == 0)
			exit(0);
		if (ft_strncmp("export ", line, 7) == 0)
			export(&root);
		if (ft_strncmp("env", line, 3) == 0)
			print_envlsts(&root);
		if (ft_strncmp("echo", line, 4) == 0)
			echo(&root);
		if (ft_strncmp("cd", line, 2) == 0)
			cd(&root);
		if (ft_strncmp("pwd", line, 3) == 0)
			pwd(&root); */
		add_history(line);
		free(line);
		line = NULL;
		//free_command(&root);
		free(prompt);
	}
	//free_command(&root);
	free_envp_array(&root);
	free_envp_lst(&root);
	free(prompt);
	free(line);
}
