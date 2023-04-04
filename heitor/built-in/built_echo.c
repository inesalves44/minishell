/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/04 21:00:07 by hmaciel-         ###   ########.fr       */
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
	if ((ft_strncmp(root->str[1], "-n", 2) == 0 && ft_strlen(root->str[1]) == 2))
		cmd++;
	while(root->str[cmd])
	{
		if (root->str[cmd][0] == '$')
		{
			if(!echo_env(root, root->str[cmd]))
				;
		}
		else
			printf("%s", root->str[cmd]);
		if (root->str != NULL)
			printf(" ");
		cmd++;
	}
	if (!(ft_strncmp(root->str[1], "-n", 2) == 0 && ft_strlen(root->str[1]) == 2))
		printf("\n");
}
