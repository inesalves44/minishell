/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:12:52 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/02 20:52:11 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_root *root, char **envp)
{
	init_envp(root, envp);
}

void	free_command(t_root *root)
{
	int	i;

	i = 0;
	while(root->ast_tree.command[i])
	{
		free(root->ast_tree.command[i]);
		i++;
	}
	free(root->ast_tree.command);
}

int main(int argc, char const *argv[], char *envp[])
{
	t_root	root;
	char	*line;
	char	*prompt;

	prompt = NULL;
	init_all(&root, envp);
	root.ast_tree.command = NULL;
	while (1)
	{
		prompt = get_prompt(&root);
		line = readline(prompt);
		root.ast_tree.command = ft_split(line, ' ');
		if (ft_strncmp("exit", line, 4) == 0)
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
			pwd(&root);
		free(line);
		free_command(&root);
		free(prompt);
	}
	free_command(&root);
	free_envp_array(&root);
	free_envp_lst(&root);
	free(prompt);
	free(line);
}
