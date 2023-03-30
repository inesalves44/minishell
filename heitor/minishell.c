/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/30 23:02:43 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "temp.h"


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


int	built_in_router(t_root *root)
{
	if (ft_strncmp(root->line, "cd", 2) == 0 || ft_strncmp(root->line, "cd ", 3) == 0)
	{
		cd(root);
		return (1);
	}
	if (ft_strncmp(root->line, "echo", 4) == 0 || ft_strncmp(root->line, "echo ", 5) == 0)
	{
		echo(root);
		return (1);
	}
	if (ft_strncmp(root->line, "pwd", 3) == 0 || ft_strncmp(root->line, "pwd ", 4) == 0)
	{
		pwd();
		return (1);
	}
	if (ft_strncmp(root->line, "env", 3) == 0 || ft_strncmp(root->line, "env ", 4) == 0)
	{
		env(root);
		return (1);
	}
	if (ft_strncmp(root->line, "exit", 4) == 0 || ft_strncmp(root->line, "exit ", 5) == 0)
	{
		ft_exit(root);
		return (1);
	}
	if (ft_strncmp(root->line, "export", 6) == 0 || ft_strncmp(root->line, "export ", 7) == 0)
	{
		export(root);
		return (1);
	}
	return (0);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_root	root;
	pid_t 	child_pid;

	(void)argc;
	(void)argv;

	init_envs(&root, envp);

	root.prompt = NULL;
	root.path = ft_split(getenv("PATH"), ':');
	int built = 0;
	while(1)
	{
		child_pid = fork();
		if(child_pid == 0)
		{
    	/* This is done by the child process. */
			get_prompt(&root);
			root.line = readline(root.prompt);
			root.command = ft_split(root.line, ' ');
			add_history(root.line);
			built = built_in_router(&root);
			if (built == 0)
    			execve(root.command[0], root.command, envp);

    	/* If execv returns, it must have failed. */
    		//exit(0);
		}
		else
		{
     	/* This is run by the parent.  Wait for the child
        to terminate. */
			waitpid(child_pid, NULL, 0);

  		}
	}
}
