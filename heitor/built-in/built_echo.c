/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/06 15:43:19 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_env(t_root *root, char *cmd)
{
	cmd++;
	return (print_env_value(root, cmd));
}

int	echo(t_root *root)
{
	int	cmd;

	cmd = 1;
	if (is_equal(root->tree->command[1], "-n"))
		cmd++;
	while (root->tree->command[cmd])
	{
		if (root->tree->command[cmd][0] == '$')
		{
			if (!echo_env(root, root->tree->command[cmd]))
				;
		}
		else
			printf("%s", root->tree->command[cmd]);
		if (root->tree->command != NULL)
			printf(" ");
		cmd++;
	}
	if (!(is_equal(root->tree->command[1], "-n")))
		printf("\n");
	return (0);
}
