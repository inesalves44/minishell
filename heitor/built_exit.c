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

void	free_array1(t_root *root)
{
	free(root->command[0]);
	free(root->command);
	free(root->line);
}

void    ft_exit(t_root *root)
{
    // funciton to free everything later!!!!
    free_array1(root);
    exit(0);
}