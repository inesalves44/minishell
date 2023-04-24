/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:23:45 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/18 16:40:50 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	sig_int(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
		redisplay_prompt();
		g_status = 130;
	}
}
