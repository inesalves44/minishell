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

void	init_envs(t_env **envs, char **envp)
{
	t_env	*node;

	while(*envp)
	{
		node = ft_lstnew_env(*envp);
		ft_lstadd_back_env(envs, node);
		envp++;
	}
}
