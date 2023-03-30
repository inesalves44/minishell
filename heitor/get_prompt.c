/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/29 15:17:25 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"

void	get_prompt(t_root *root)
{
	char 	*home;
	char	*path;

	path = get_pwd();
	home = getenv("HOME");
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		root->prompt = ft_strjoin("\033[1m\033[32m", getenv("USER"));
		root->prompt = ft_strjoin(root->prompt, "@miniteam:\033[1m\033[34m~");
		root->prompt = ft_strjoin(root->prompt, path + ft_strlen(home));
		root->prompt = ft_strjoin(root->prompt, "$ \033[0m");
	}
	else
	{
		root->prompt = ft_strjoin("\033[1m\033[32m", getenv("USER"));
		root->prompt = ft_strjoin(root->prompt, "@miniteam:\033[1m\033[34m~");
		root->prompt = ft_strjoin(root->prompt, path);
		root->prompt = ft_strjoin(root->prompt, "$ \033[0m");
	}
}