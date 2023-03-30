/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:13:13 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/29 16:13:15 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"

void	free_array(t_root *root)
{
	int	i = 0;
	while(root->command[i])
	{
        printf("%s",root->command[i]);
		free(root->command[i]);
		i++;
	}
	free(root->command);
	free(root->line);
	free(root->prompt);
}

void    ft_exit(t_root *root)
{
    free_array(root);
    exit(0);
}