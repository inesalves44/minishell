/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:16:13 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/05 10:48:53 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_key_node(t_root *root, char *key)
{
	t_envlst	*head;
	t_envlst	*tmp;

	tmp = NULL;
	printf("%s", key);
	printf("%s", root->env_lst->key);
	head = root->env_lst;
	while (root->env_lst && root->env_lst->next)
	{
		if (ft_strncmp(root->env_lst->next->key, key, ft_strlen(key)) == 0)
		{
			printf("igual - apagar\n");
			tmp = root->env_lst->next->next;
			root->env_lst->next = NULL;
			root->env_lst->next = tmp;
			break ;
		}
		root->env_lst = root->env_lst->next;
	}
	root->env_lst = head;
	refresh_env_array(root);
}

void	unset(t_root *root)
{
	find_key_node(root, root->tree->command[1]);
}
