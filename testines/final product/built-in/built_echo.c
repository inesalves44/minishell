/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/06 21:26:49 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	echo_env(t_root *root, char *cmd)
{
	cmd++;
	return(print_env_value(root, cmd));
}

void    echo(t_root *root)
{
    int     cmd;

	cmd = 1;
	if ((ft_strncmp(root->tree->command[1], "-n", 2) == 0 && ft_strlen(root->tree->command[1]) == 2))
		cmd++;
	while(root->tree->command[cmd])
	{
		if (root->tree->command[cmd][0] == '$' && root->tree->squotes[cmd] == -1)
		{
			if(!echo_env(root, root->tree->command[cmd]))
				break ;
		}
		else
			write(root->out, root->tree->command[cmd], ft_strlen(root->tree->command[cmd]));//printf("%s", root->tree->command[cmd]);
		if (root->tree->command != NULL)
			write(root->out, " ", 1);//printf(" ");
		cmd++;
	}
	if (!(ft_strncmp(root->tree->command[1], "-n", 2) == 0 && ft_strlen(root->tree->command[1]) == 2))
		write(root->out, "\n", 1);//printf("\n");
}
