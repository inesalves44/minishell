/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:48:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/04 13:23:02 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	init_all(t_root *root, char **envp)
{
	root->lexer = NULL;
	root->tree = NULL;
	root->env_array = NULL;
	root->env_lst = NULL;
	root->prompt = NULL;
	root->user = NULL;
	root->prompt = NULL;
	root->line = NULL;
	root->pipes = NULL;
	root->status = 0;
	root->status_old = 0;
	init_envp(root, envp);
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
		root.prompt = get_prompt(&root);
		root.line = readline(root.prompt);
		if (root.line == NULL)
			break ;
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
	free_all(&root, 0);
}
