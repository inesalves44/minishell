/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:11:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/06 12:24:24 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_to_home(t_root *root)
{
	char	*path;

	path = get_env_value(root, "HOME");
	chdir(path);
	change_value(root, "PWD", path);
	if (path)
		free(path);
}

int	has_more_params_error(int size)
{
	if (size > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR);
		return (1);
	}
	return (0);
}

void	refresh_pwd_env(t_root *root)
{
	char	*path;

	path = get_pwd();
	change_value(root, "PWD", path);
	free(path);
}

int	cd(t_root *root)
{
	char	*path;

	path = NULL;
	if (get_array_size(root->str) == 1)
	{
		change_to_home(root);
		return (0);
	}
	if (has_more_params_error(get_array_size(root->str)))
		return (1);
	else
	{
		if (chdir(root->str[1]) == 0)
			refresh_pwd_env(root);
		else
		{
			ft_putstr_fd("minishell: cd: ", STDERR);
			ft_putstr_fd(root->str[1], STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
			return (1);
		}
	}
	return (0);
}
