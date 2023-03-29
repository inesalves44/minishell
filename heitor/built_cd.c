/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:11:12 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/29 15:11:15 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"

void	cd(t_root *root)
{
	int		size;
	char	*err;

	size = array_size(root->command);

	if(size == 1)
		chdir(getenv("HOME"));
	else if (size > 2)
		printf("minishell: cd: too many arguments\n");
	else
	{
		err = ft_strjoin("minishell: cd: ", root->command[1]);
		if (chdir(root->command[1]) != 0)
		{
			perror(err);
		}
		free(err);
	}
}