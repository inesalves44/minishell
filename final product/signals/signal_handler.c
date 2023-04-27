/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:23:45 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/27 11:26:38 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

extern int	g_status;

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		redisplay_prompt();
		g_status = 130;
	}
}

void	sig_int2(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 130;
	}
}

void	sig_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)", STDERR);
		kill(0, SIGINT);
		g_status = 131;
	}
}
