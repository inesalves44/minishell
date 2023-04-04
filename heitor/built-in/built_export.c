/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:47:57 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/04 20:25:30 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_error(const char *arg)
{
	int		i;

	i = -1;
	if (arg[0] == '$')
	{
			ft_putstr_fd("minishell: export: `", STDERR);
			while(arg[++i])
				write(STDERR, &arg[i], 1);
			ft_putstr_fd("\': not a valid identifier\n", STDERR);
			return (TRUE);
	}
	else if (ft_strchr(arg, '=') == NULL)
	{
		ft_putstr_fd("\n", STDERR);
		return (TRUE);
	}
	return (FALSE);
}

void	export(t_root *root)
{
	char	*key;
	char	*value;
	int		param;

	param = 1;
	while (root->str[param])
	{
		if (has_error(root->str[param]))
			break ;
		else
		{
			key = get_key_from_str(root->str[1]);
			value = get_value_from_str(root->str[1]);
			if (!change_value(root, key, value))
			{
				ft_lstadd_back_env(&root->env_lst, ft_lstnew_env(key,value));
			}
		}
		param++;
	}
	refresh_env_array(root);
}
