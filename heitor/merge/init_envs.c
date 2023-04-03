/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:37:54 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/02 17:32:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_array_size(char **array)
{
	int	i;

	i = 0;
	while(array[i])
		i++;
	return (i);
}

int	get_lst_size(t_envlst *lst)
{
	t_envlst	*head;
	int			i;

	i =0;
	head = lst;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_keylen(char *env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	return (i);
}

char	*extract_key(char *env)
{
	char	*temp_key;
	int		i;
	int		size;

	i = 0;
	size = ft_keylen(env);
	temp_key = ft_calloc(sizeof(char), size + 1);
	ft_memcpy(temp_key, env, size);
	return (temp_key);
}

char	*extract_value(char *env)
{
	char	*temp_value;
	int		i;
	int		size;

	i = 0;
	size = ft_keylen(env);
	temp_value = ft_calloc(sizeof(char), (ft_strlen(env) - size) + 1);
	ft_memcpy(temp_value, env + size + 1, ft_strlen(env) - size);
	return (temp_value);
}

void	init_envp(t_root *root, char **envp)
{
	char	*key;
	char	*value;
	int		size;
	int		i;

	i = 0;
	size = get_array_size(envp);
	root->my_envp.env_array = malloc(sizeof(char *) * (size + 1));
	root->my_envp.env_array[size] = 0;
	root->my_envp.env_lst = NULL;
	while(*envp)
	{
		root->my_envp.env_array[i] = ft_strdup(*envp);
		key = extract_key(*envp);
		value = extract_value(*envp);
		ft_lstadd_back_env(&root->my_envp.env_lst, ft_lstnew_env(key, value));
		envp++;
		i++;
	}
}
