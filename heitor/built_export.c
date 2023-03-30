/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:47:57 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/29 22:07:38 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"

int	change_value(t_root *root, char *key, char *new_value)
{
	t_env	*head;

	head = root->envs;
	while(root->envs)
	{

		if (ft_strncmp(key, root->envs->key, ft_strlen(key)) == 0)
		{
			root->envs->value = ft_strdup(new_value);
			root->envs = head;
			return (1);
		}
		root->envs = root->envs->next;
	}
	root->envs = head;
	return (0);
}

void	export(t_root *root)
{
	t_env	*var;
	char	*key;
	char	*value;

	key = extract_key(root->command[1]);
	value = extract_value(root->command[1]);
	if (!change_value(root, key, value))
	{
		var = ft_lstnew_env(key, value);
		ft_lstadd_back_env(&root->envs, var);
	}
}
