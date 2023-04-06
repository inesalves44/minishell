/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:48:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/06 16:00:17 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		print_envlsts(root);
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

	/*temporary tree initialization*/
	root.tree = malloc(sizeof(t_ast));
	root.tree->file = NULL;
	root.tree->command = NULL;
	root.tree->left = NULL;
	root.tree->node = 0;
	root.tree->prev = NULL;
	root.tree->quotes = 0;
	root.tree->rigth = NULL;
	root.tree->type = 0;

	root.line = NULL;
	(void)argc;
	(void)argv;
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = sig_int;
	sig.sa_flags = SA_SIGINFO;

	init_envp(&root, envp);
	root.user = get_env_value(&root, "USER");
	sigaction(SIGINT, &sig, NULL);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		root.prompt = get_prompt(&root);
		root.line = readline(root.prompt);
		if (root.line == NULL)
			free_all(&root);
    	root.tree->command = ft_split(root.line, ' ');
		if (ft_strlen(root.line) > 0)
			built_in_router(&root);
		add_history(root.line);
		free(root.line);
		free(root.prompt);
		free_array(root.tree->command);
		root.tree->command = NULL;
	}
}
