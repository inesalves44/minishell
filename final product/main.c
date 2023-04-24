/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:48:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/24 11:17:32 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	init_all(t_root *root, char **envp)
{
	init_envp(root, envp);
	root->status = 0;
	root->status_old = 0;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
void	free_all(t_root *root)
{
	if (root->tree != NULL)
		root->tree = free_tree(root->tree, 0);
	if (root->lexer != NULL)
		root->lexer = free_lexer(root->lexer);
	free_envp_lst(root);
	free_array(root->env_array);
	/* if (root->tree->command)
		free_array(root->tree->command); */
	free(root->user);
	free(root->prompt);
	free(root->line);
	rl_clear_history();
	printf("exit\n");
}

int	built_in_router(t_root *root)
{
	if (is_equal(root->tree->command[0], "cd"))
		return (cd(root));
	if (is_equal(root->tree->command[0], "echo"))
		return (echo(root));
	if (is_equal(root->tree->command[0], "env"))
		return (env(root));
	if (is_equal(root->tree->command[0], "export"))
		return (export(root));
	if (is_equal(root->tree->command[0], "pwd"))
		return (pwd(root));
	if (is_equal(root->tree->command[0], "exit"))
		return (ft_exit(root));
	if (is_equal(root->tree->command[0], "unset"))
		return (unset(root));
	return (FALSE);
}


int main(int argc, char const *argv[], char *envp[])
{
	t_root	root;

	root.prompt = NULL;
	root.line = NULL;
	(void)argc;
	(void)argv;

	init_all(&root, envp);
	root.user = get_env_value(&root, "USER");
	signal(SIGQUIT, SIG_IGN);
	root.tree = NULL;
	root.lexer = NULL;
	while (1)
	{
		signal(SIGINT, sig_int);
		root.prompt = get_prompt(&root);
		root.line = readline(root.prompt);
    	if (!lexical_annalysis(&root.lexer, root.line))
		{
			root.tree = NULL;
			if (g_status == 130)
				root.status_old = 130;
			else
				root.status_old = root.status;
			if(!parsing_str(&root.lexer, &root.tree))
			{
				root.in = 0;
				root.out = 1;
				root.status = 0;
				root.status = checking_processes(&root);
			//	printf("\n status: %d\n", root.status);
			}
		}
		add_history(root.line);
		free(root.line);
		root.line = NULL;
		free(root.prompt);
		if (root.tree != NULL)
			root.tree = free_tree(root.tree, 0);
		if (root.lexer != NULL)
			root.lexer = free_lexer(root.lexer);
	}
	free_all(&root);
}
