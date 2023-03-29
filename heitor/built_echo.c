/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/03/29 15:25:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"

void    echo(t_root *root)
{
    int     element;

    element = 1;
    while(root->command[element])
    {
        printf("%s", root->command[element]);
        if (root->command[element + 1] != NULL)
            printf(" ");
        element++;
    }
    printf("\n");
}