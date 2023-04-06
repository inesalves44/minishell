/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:47:57 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/06 15:43:13 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_error(const char *arg)
{
	int		i;

	i = -1;
	if (arg[0] == '$' || arg[0] == '=')
	{
		ft_putstr_fd("minishell: export: `", STDERR);
		while (arg[++i])
			write(STDERR, &arg[i], 1);
		ft_putstr_fd("\': not a valid identifier\n", STDERR);
		return (TRUE);
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
		if (has_error(root->tree->command[cmd]))
			ret = 1;
		else if (ft_strchr(root->tree->command[cmd], '=') != NULL)
		{
			key = get_key_from_str(root->tree->command[cmd]);
			value = get_value_from_str(root->tree->command[cmd]);
			if (!change_value(root, key, value))
			{
				ft_lstadd_back_env(&root->env_lst, ft_lstnew_env(key, value));
			}
		}
		cmd++;
	}
	refresh_env_array(root);
	return (ret);
}
