/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:48:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/10 22:06:44 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 0;

void	init_all(t_root *root, char **envp)
{
	init_envp(root, envp);
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
int	free_all(t_root *root)
{
	free_envp_lst(root);
	free_array(root->env_array);
	if (root->tree->command)
		free_array(root->tree->command);
	free(root->user);
	free(root->prompt);
	free(root->line);
	rl_clear_history();
	printf("exit\n");
	exit(0);
}

int	built_in_router(t_root *root)
{
	if (is_equal(root->tree->command[0], "cd"))
		cd(root);
	if (is_equal(root->tree->command[0], "echo"))
		echo(root);
	if (is_equal(root->tree->command[0], "env"))
		env(root);
	if (is_equal(root->tree->command[0], "export"))
		export(root);
	if (is_equal(root->tree->command[0], "pwd"))
		pwd(root);
	if (is_equal(root->tree->command[0], "exit"))
		free_all(root);
	if (is_equal(root->tree->command[0], "unset"))
		unset(root);
	return (FALSE);
}


int main(int argc, char const *argv[], char *envp[])
{
	t_root	root;

	root.prompt = NULL;
	root.line = NULL;
	(void)argc;
	(void)argv;
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = sig_int;
	sig.sa_flags = SA_SIGINFO;

	init_all(&root, envp);
	root.user = get_env_value(&root, "USER");
	sigaction(SIGINT, &sig, NULL);
	signal(SIGQUIT, SIG_IGN);
	root.tree = NULL;
	root.lexer = NULL;
	while (1)
	{
		root.prompt = get_prompt(&root);
		root.line = readline(root.prompt);
		if (root.line && !ft_strncmp(root.line, "exit", 4))
			exit(EXIT_SUCCESS);
    	if (!lexical_annalysis(&root.lexer, root.line))
		{
			root.tree = NULL;
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
		if (g_sig == 1)
			free_all(&root);
	}
}
