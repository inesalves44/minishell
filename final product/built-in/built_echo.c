/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/27 11:57:00 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	do_print_echo(t_root *root, char *cmd)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while (i < ft_strlen(cmd))
	{
		ft_putchar_fd(cmd[i], root->out);
		i++;
	}
	return (1);
}

static int	loop_echo(t_root *root)
{
	int	cmd;

	cmd = 1;
	while (is_equal(root->tree->command[cmd], "-n") && root->tree->command[cmd])
			cmd++;
	while (root->tree->command[cmd])
	{
		do_print_echo(root, root->tree->command[cmd]);
		cmd++;
		if (root->tree->command[cmd])
			ft_putchar_fd(' ', root->out);
	}
	if (!is_equal(root->tree->command[1], "-n"))
		ft_putchar_fd('\n', root->out);
	return (0);
}

int	echo(t_root *root)
{
	if (get_array_size(root->tree->command) <= 1)
		ft_putchar_fd('\n', root->out);
	else
		loop_echo(root);
	return (0);
}
