/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/03 16:50:26 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo(t_root *root)
{
    int     cmd;
	char	*key;
	int		print_space;

	// TODO if init with $ check if the env var exist.
    cmd = 1;
	key = NULL;
	print_space = TRUE;
	while(root->tree->command[cmd])
	{
		if (root->tree->command[cmd][0] == '$')
		{
			key = extract_key(root->tree->command[cmd]);
			if (ft_strlen(root->tree->command[cmd]) - 1 == ft_strlen(key+1))
			{
				if(!print_env_value(root, key+1))
					print_space = FALSE;
				else
					print_space = TRUE;
			}
			free(key);
		}
		else
		{
			print_space = TRUE;
			printf("%s", root->tree->command[cmd]);
		}
		if (root->tree->command[cmd + 1] != NULL && print_space)
			printf(" ");
		cmd++;
	}
	printf("\n");
}
