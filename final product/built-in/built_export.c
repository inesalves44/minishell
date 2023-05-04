/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:47:57 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/05/04 10:29:28 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_error(char *key)
{
	int		i;

	i = -1;
	if (!key || ft_strlen(key) == 0)
	{
		ft_putstr_fd("minishell: export: `", STDERR);
		ft_putstr_fd("=", STDERR);
		ft_putstr_fd("\': not a valid identifier\n", STDERR);
		return (TRUE);
	}
	return (FALSE);
}

static void	print_export(t_root *root)
{
	char		*key;
	char		*value;
	int			i;

	i = 0;
	while (root->env_array[i])
	{
		key = get_key_from_str(root->env_array[i]);
		if (key)
		{
			ft_putstr_fd("declare -x ", root->out);
			ft_putstr_fd(key, root->out);
			value = get_value_from_str(root->env_array[i]);
			if (value)
			{
				ft_putstr_fd("=\"", root->out);
				ft_putstr_fd(value, root->out);
				ft_putstr_fd("\"", root->out);
				free(value);
			}
			ft_putstr_fd("\n", root->out);
		}
		free(key);
		i++;
	}
}

void	do_change(t_root *root, char *key, char *value)
{
	if (!change_value(root, key, value))
		ft_lstadd_back_env(&root->env_lst, ft_lstnew_env(key, value));
}

int	export(t_root *root)
{
	char	*key;
	char	*value;
	int		cmd;
	int		ret;

	ret = 0;
	cmd = 1;
	if (get_array_size(root->tree->command) == 1)
		print_export(root);
	else
	{
		while (root->tree->command[cmd])
		{
			key = get_key_from_str(root->tree->command[cmd]);
			value = get_value_from_str(root->tree->command[cmd]);
			if (has_error(key))
			{
				ret = 1;
				free(key);
				free(value);
			}
			else
				do_change(root, key, value);
			cmd++;
		}
		refresh_env_array(root);
	}
	return (ret);
}
