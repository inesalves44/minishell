/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:37:54 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/04 10:18:46 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_key_from_str(char *env)
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

char	*get_value_from_str(char *env)
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
	root->env_array = malloc(sizeof(char *) * (size + 1));
	root->env_array[size] = 0;
	root->env_lst = NULL;
	while(*envp)
	{
		root->env_array[i] = ft_strdup(*envp);
		key = get_key_from_str(*envp);
		value = get_value_from_str(*envp);
		ft_lstadd_back_env(&root->env_lst, ft_lstnew_env(key, value));
		envp++;
		i++;
	}
}
