/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:25 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/29 20:56:21 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../temp.h"

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast_env(t_env *envs)
{
	while (envs)
	{
		if (envs->next)
			envs = envs->next;
		else
			break ;
	}
	return (envs);
}

void	ft_lstadd_back_env(t_env **envs, t_env *new)
{
	t_env	*node;
	if (new)
		{
		if (!envs[0])
			envs[0] = new;
		else
		{
			node = ft_lstlast_env(*envs);
			node->next = new;
		}
	}
}

void	print_envs(t_root *root)
{
	t_env	*head;

	head = root->envs;
	while(root->envs)
	{
		printf("%s", root->envs->key);
		printf("%s\n", root->envs->value);
		root->envs = root->envs->next;
	}
	root->envs = head;
}
