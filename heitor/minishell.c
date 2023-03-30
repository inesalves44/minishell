/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/29 22:06:52 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "temp.h"


/* void sig_interruption(int sig, siginfo_t *info, void *context) {

	t_root *root;

	root = (t_root *)context;
	(void)info;
	(void)context;
	if (sig == SIGTERM)
		exit(1);
	if (sig == SIGINT)
		return;
 } */

 void	free_all(t_root *root)
 {
	int	i = 0;
	while(root->command[i])
	{
		free(root->command[i]);
		i++;
	}
	free(root->command);
	free(root->line);
	free(root->prompt);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_root				root;
/* 	struct sigaction sa = {0}; */

	(void)argc;
	(void)argv;

	init_envs(&root, envp);

/* 	sa.sa_sigaction = sig_interruption; */
 
	
//	char *command_args[] = { "ls", NULL};
//	execve("/usr/bin/ls", command_args, envp);

	root.prompt = NULL;

	while(1)
	{
/* 		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL); */
		get_prompt(&root);
		root.line = readline(root.prompt);
		root.command = ft_split(root.line, ' ');

		if (ft_strncmp(root.line, "cd", 2) == 0 || ft_strncmp(root.line, "cd ", 3) == 0)
		{
			cd(&root);
		}
		if (ft_strncmp(root.line, "echo", 4) == 0 || ft_strncmp(root.line, "echo ", 5) == 0)
		{
			echo(&root);
		}
		if (ft_strncmp(root.line, "pwd", 3) == 0 || ft_strncmp(root.line, "pwd ", 4) == 0)
		{
			pwd();
		}
		if (ft_strncmp(root.line, "env", 3) == 0 || ft_strncmp(root.line, "env ", 4) == 0)
		{
			env(&root);
		}
		if (ft_strncmp(root.line, "exit", 4) == 0 || ft_strncmp(root.line, "exit ", 5) == 0)
		{
			ft_exit(&root);
		}
		if (ft_strncmp(root.line, "export", 6) == 0 || ft_strncmp(root.line, "export ", 7) == 0)
		{
			export(&root);
		}
		add_history(root.line);
		free_all(&root);
	}
}
