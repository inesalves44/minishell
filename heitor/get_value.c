/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:35:27 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/02 18:14:35 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_env_array(t_root *root)
{
	t_envlst	*head;
	int			size;
	int			i;

	i = 0;
	size = get_lst_size(root->my_envp.env_lst);
	free_envp_array(root);
	root->my_envp.env_array = malloc(sizeof(char*) * (size + 1));
	root->my_envp.env_array[size] = 0;
	head = root->my_envp.env_lst;
	while (root->my_envp.env_lst)
	{
		root->my_envp.env_array[i] = NULL;
		root->my_envp.env_array[i] = ft_strjoin_gnl(root->my_envp.env_array[i], root->my_envp.env_lst->key);
		root->my_envp.env_array[i] = ft_strjoin_gnl(root->my_envp.env_array[i], "=");
		root->my_envp.env_array[i] = ft_strjoin_gnl(root->my_envp.env_array[i], root->my_envp.env_lst->value);
		i++;
		root->my_envp.env_lst = root->my_envp.env_lst->next;
	}
	root->my_envp.env_lst = head;
}

char    *get_env_value(t_root *root, char *key)
{
    t_envlst	*head;
	char		*ret;

	head = root->my_envp.env_lst;
	ret = NULL;
	while(root->my_envp.env_lst)
	{

		if (ft_strncmp(key, root->my_envp.env_lst->key, ft_strlen(key)) == 0)
		{
			ret = root->my_envp.env_lst->value;
			break ;
		}
		root->my_envp.env_lst = root->my_envp.env_lst->next;
	}
	root->my_envp.env_lst = head;
	return (ret);
}

int    print_env_value(t_root *root, char *key)
{
    t_envlst	*head;

	head = root->my_envp.env_lst;
	while(root->my_envp.env_lst)
	{
		if (ft_strncmp(key, root->my_envp.env_lst->key, ft_strlen(root->my_envp.env_lst->key)) == 0)
		{
			printf("%s", root->my_envp.env_lst->value);
			root->my_envp.env_lst = head;
			return (TRUE);
		}
		root->my_envp.env_lst = root->my_envp.env_lst->next;
	}
	root->my_envp.env_lst = head;
	return (FALSE);
}
