/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:29:11 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/11 09:32:04 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dq_print(t_root *root, char *cmd)
{
	while (*cmd)
	{
		ft_putchar_fd(*cmd, root->out);
		cmd++;
	}
	return (1);
}

int	handler_special(t_root *root, char c)
{
	if (c == '$')
		ft_putnbr_fd(getpid(), root->out);
	else
		ft_putnbr_fd(root->status, root->out);
	return (1);
}