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

void	export(t_root *root, t_env **envs)
{
	t_env	*var;

	var = ft_lstnew_env(root->command[1]);
	ft_lstadd_back_env(envs, var);
}
