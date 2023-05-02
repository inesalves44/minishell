/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:48:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/28 18:53:11 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	init_all(t_root *root, char **envp)
{
	root->prompt = NULL;
	root->line = NULL;
	init_envp(root, envp);
	root->status = 0;
	root->status_old = 0;
	root->tree = NULL;
	root->lexer = NULL;
}

void	get_status(t_root *root)
{
	if (g_status == 130)
		root->status_old = 130;
	else if (g_status == 131)
		root->status_old = 131;
	else
		root->status_old = root->status;
	g_status = 0;
}

static void	go_process(t_root *root)
{
	root->in = 0;
	root->out = 1;
	root->status = 0;
	root->status = checking_processes(root);
}

int	main(int argc, char const *argv[], char *envp[])
{
	t_root	root;

	(void)argc;
	(void)argv;
	init_all(&root, envp);
	root.user = get_env_value(&root, "USER");
	while (1)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		root.prompt = get_prompt(&root);
		root.line = readline(root.prompt);
		add_history(root.line);
		if (!lexical_annalysis(&root.lexer, root.line))
		{
			root.tree = NULL;
			get_status(&root);
			if (!parsing_str(&root.lexer, &root.tree))
				go_process(&root);
		}
		mini_free(&root);
	}
	free_all(&root);
}
