/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:42:25 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/02 17:36:32 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*ft_lstnew_env(char *key, char *value)
{
	t_envlst	*node;

	node = malloc(sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->key = (char *)key;
	node->value = (char *)value;
	node->next = NULL;
	return (node);
}

t_envlst	*ft_lstlast_envlst(t_envlst *envs)
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

void	ft_lstadd_back_env(t_envlst **envs, t_envlst *new)
{
	t_envlst	*node;
	if (new)
		{
		if (!envs[0])
			envs[0] = new;
		else
		{
			node = ft_lstlast_envlst(*envs);
			node->next = new;
		}
	}
}

void	print_envlsts(t_root *root)
{
	t_envlst	*head;

	head = root->my_envp.env_lst;
	while(root->my_envp.env_lst)
	{
		printf("%s", root->my_envp.env_lst->key);
		printf("=");
		printf("%s\n", root->my_envp.env_lst->value);
		root->my_envp.env_lst = root->my_envp.env_lst->next;
	}
	root->my_envp.env_lst = head;
}

void	free_envp_lst(t_root *root)
{
	t_envlst	*temp;

	while (root->my_envp.env_lst)
	{

		temp = root->my_envp.env_lst->next;
		free(root->my_envp.env_lst->key);
		free(root->my_envp.env_lst->value);
		free(root->my_envp.env_lst);
		root->my_envp.env_lst = temp;
	}
	free(temp);
	free(root->my_envp.env_lst);
}

void	free_envp_array(t_root *root)
{
	int	i;

	i = 0;
	while(root->my_envp.env_array[i])
	{
		free(root->my_envp.env_array[i]);
		i++;
	}
	free(root->my_envp.env_array);
}
