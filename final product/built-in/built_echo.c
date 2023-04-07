/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/07 21:11:27 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char c)
{
	if (c == '$' || c == '?')
		return (1);
	return (0);
}

int	echo_env(t_root *root, char *cmd)
{
	cmd++;
	return (print_env_value(root, cmd));
}

int	echo(t_root *root)
{
	int	cmd;
	int	i;

	i = 0;
	cmd = 1;
	if (is_equal(root->tree->command[1], "-n"))
		cmd++;
	while (root->tree->command[cmd])
	{
		if (root->tree->command[cmd][0] == '$' && !is_special_char(root->tree->command[cmd][1]))
			echo_env(root, root->tree->command[cmd]);
		else
		{
			while(root->tree->command[cmd][i])
			{
				if (root->tree->command[cmd][i] == '$' && root->tree->command[cmd][i+1] == '$')
				{
					ft_putnbr_fd(getpid(), root->out);
					i++;
				}
				else
				{
					ft_putchar_fd(root->tree->command[cmd][i], root->out);
				}
				i++;
			}
		}
		if (root->tree->command[cmd+1])
			ft_putchar_fd(' ', root->out);
		cmd++;
		i = 0;
	}
	if (!(is_equal(root->tree->command[1], "-n")))
		ft_putchar_fd('\n', root->out);
	return (0);
}
