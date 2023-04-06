/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:44 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/06 18:17:06 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	*pwd;

	pwd = get_pwd();
	if (pwd)
	{
		ft_putstr_fd(pwd, STDOUT);
		ft_putchar_fd('\n', STDOUT);
		free(pwd);
	}
	return (0);
}
