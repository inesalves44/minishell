/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:47:57 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/11 07:46:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_error(char *key, char *value)
{
	int		i;

	i = -1;
	if (!key)
		return (TRUE);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR);
			ft_putstr_fd(key, STDERR);
			ft_putstr_fd("=", STDERR);
			ft_putstr_fd(value, STDERR);
			ft_putstr_fd("\': not a valid identifier\n", STDERR);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	export(t_root *root)
{
	char	*key;
	char	*value;
	int		cmd;
	int		ret;

	ret = 0;
	cmd = 1;
	while (root->tree->command[cmd])
	{
		key = get_key_from_str(root->tree->command[cmd]);
		value = get_value_from_str(root->tree->command[cmd]);
		if (has_error(key, value))
			ret = 1;
		else if (ft_strchr(root->tree->command[cmd], '=') != NULL)
		{
			if (!change_value(root, key, value))
				ft_lstadd_back_env(&root->env_lst, ft_lstnew_env(key, value));
		}
		cmd++;
	}
	refresh_env_array(root);
	return (ret);
}
