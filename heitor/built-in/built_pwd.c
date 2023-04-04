/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:44 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/04 20:57:49 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void   pwd(t_root *root)
{
	char	*pwd;

	pwd = get_env_value(root, "PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
