/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/28 20:17:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/includes/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>





/*void sig_interruption(int sig, siginfo_t *info, void *context) {
    printf("You pressed ctrl+c, do something!\n");
 }*/


void	cd(char *path)
{
	chdir(path);
}


char *get_username(char **env)
{
	char *user;

	user = NULL;
	while(*env)
	{
		if (ft_strncmp(*env, "USER=", 5) == 0)
		{
			user = *env;
			break ;
		}
		env++;
	}
	return (user + 5);
}


void	get_prompt(char **env)
{
	char cwd[100];
	char	*user;
	printf("\033[1m\033[32m%s@miniteam:\033[1m\033[34m%s$", get_username(env), getcwd(cwd, 100));
	printf("\033[0m"); //reset
}


int	main(int argc, char *argv[], char *envp[])
{
	char *line;
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
		get_prompt(envp);
		line = readline(" ");
		if (ft_strncmp(line, "cd ", 3) == 0)
			cd(line + 3);
		add_history(line);
	}
}
