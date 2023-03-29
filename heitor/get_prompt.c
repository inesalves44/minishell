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

void	get_prompt()
{
	char cwd[BUFFER_PATH];
	char *home;

	home = getenv("HOME");
	if (ft_strncmp(getcwd(cwd, 100), home, ft_strlen(home)) == 0)
		printf("\033[1m\033[32m%s@miniteam:\033[1m\033[34m~%s$", getenv("USER"), getcwd(cwd, BUFFER_PATH) + ft_strlen(home));
	else
		printf("\033[1m\033[32m%s@miniteam:\033[1m\033[34m%s$", getenv("USER"), getcwd(cwd, BUFFER_PATH));
	printf("\033[0m"); //reset
}