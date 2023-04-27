/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:58:59 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/27 11:56:56 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_all_num(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '+' || cmd[i] == '-')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_root *root)
{
	int	temp_exit;

	temp_exit = 0;
	if (get_array_size(root->tree->command) == 1)
		temp_exit = 0;
	else if (get_array_size(root->tree->command) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		temp_exit = 1;
	}
	else
	{
		if (is_all_num(root->tree->command[1]))
			temp_exit = ft_atoi(root->tree->command[1]);
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR);
			temp_exit = 2;
		}
	}
	free_all(root);
	exit(temp_exit);
}
