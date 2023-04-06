/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:48:07 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/06 23:52:19 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int g_sig = 0;

void	redisplay_prompts()
{
	rl_reset_line_state();      // Resets the display state to a clean state
  	rl_cleanup_after_signal();  // Resets the terminal to the state before readline() was called
  	rl_replace_line("",0);      // Clears the current prompt
  	rl_crlf();                  // Moves the cursor to the next line
  	rl_redisplay();
}
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

int	is_built(char **commands)
{
	if (ft_strncmp(commands[0],"cd", 2) == 0 && ft_strlen(commands[0]) == 2)
		return (TRUE);
	if (ft_strncmp(commands[0],"echo", 4) == 0 && ft_strlen(commands[0]) == 4)
		return (TRUE);
	if (ft_strncmp(commands[0],"env", 3) == 0 && ft_strlen(commands[0]) == 3)
		return (TRUE);
	if (ft_strncmp(commands[0],"export", 6) == 0 && ft_strlen(commands[0]) == 6)
		return (TRUE);
	if (ft_strncmp(commands[0],"pwd", 3) == 0 && ft_strlen(commands[0]) == 3)
		return (TRUE);
	if (ft_strncmp(commands[0],"exit", 4) == 0 && ft_strlen(commands[0]) == 4)
		return (TRUE);
	return (FALSE);
}

int	free_all(t_root *root)
{
	free_envp_lst(root);
	free_array(root->env_array);
	free(root->user);
	free(root->prompt);
	free(root->line);
	rl_clear_history();
	printf("exit\n");
	exit(0);
}

int	built_in_router(t_root *root)
{
	if (ft_strncmp(root->tree->command[0],"cd", 2) == 0 && ft_strlen(root->tree->command[0]) == 2)
		cd(root);
	if (ft_strncmp(root->tree->command[0],"echo", 4) == 0 && ft_strlen(root->tree->command[0]) == 4)
		echo(root);
	if (ft_strncmp(root->tree->command[0],"env", 3) == 0 && ft_strlen(root->tree->command[0]) == 3)
		print_envlsts(root);
	if (ft_strncmp(root->tree->command[0],"export", 6) == 0 && ft_strlen(root->tree->command[0]) == 6)
		export(root);
	if (ft_strncmp(root->tree->command[0],"pwd", 3) == 0 && ft_strlen(root->tree->command[0]) == 3)
		pwd(root);
	if (ft_strncmp(root->tree->command[0],"exit", 4) == 0 && ft_strlen(root->tree->command[0]) == 4)
		free_all(root);
	if (ft_strncmp(root->tree->command[0],"unset", 5) == 0 && ft_strlen(root->tree->command[0]) == 5)
		unset(root);
	return (FALSE);
}

static	void	sig_int(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
		redisplay_prompts();
	if (sig == SIGQUIT)
	{
		g_sig = 1;
	}
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
				root.status = checking_processes(&root);		
			}
		}
		add_history(root.line);
		free(root.line);
		root.line = NULL;
		free(root.prompt);
		if (root.tree != NULL)
			free_tree(&root.tree, 0);
		if (root.lexer != NULL)
			free_lexer(&root.lexer);
		if (g_sig == 1)
			free_all(&root);
	}
}
