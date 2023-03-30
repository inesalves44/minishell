/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:37:54 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/29 22:02:23 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../temp.h"

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
	return (i + 1);
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
	ft_memcpy(temp_value, env + size, ft_strlen(env) - size);
	return (temp_value);
}


void	init_envs(t_root *root, char **envp)
{
	char	*key;
	char	*value;

	root->envs = NULL;
	while(*envp)
	{
		key = extract_key(*envp);
		value = extract_value(*envp);
		ft_lstadd_back_env(&root->envs, ft_lstnew_env(key, value));
		free(key);
		free(value);
		envp++;
	}
}
