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


/*void sig_interruption(int sig, siginfo_t *info, void *context) {
    printf("You pressed ctrl+c, do something!\n");
 }*/


int	main(int argc, char *argv[], char *envp[])
{
	t_root	root;
	t_env	*envs;
	(void)argc;
	(void)argv;

	init_envs(&envs, envp);
/*
	struct sigaction	sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_interruption;

	sigaction(SIGINT, &sa, NULL);
*/
//	char *command_args[] = { "ls", NULL};
//	execve("/usr/bin/ls", command_args, envp);


	while(1)
	{
		get_prompt();
		root.line = readline(" ");
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
			env(envs);
		}
		if (ft_strncmp(root.line, "exit", 4) == 0 || ft_strncmp(root.line, "exit ", 5) == 0)
		{
			ft_exit(&root);
		}
		if (ft_strncmp(root.line, "export", 6) == 0 || ft_strncmp(root.line, "export ", 7) == 0)
		{
			export(&root, &envs);
		}
		add_history(root.line);
		free(root.command[0]);
		free(root.command);
		free(root.line);
		//free(root.command);
	}
}
