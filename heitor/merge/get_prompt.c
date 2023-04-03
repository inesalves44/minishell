/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:05:02 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/02 17:31:36 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dest;
	size_t	len;

	len = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_calloc(sizeof(char) ,len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, ft_strlen(s1));
	ft_memcpy(dest + ft_strlen(s1), s2, ft_strlen(s2));
	free(s1);
	return (dest);
}

char	*get_prompt(t_root *root)
{
	char	*prompt;
	int		size;

	size = ft_strlen(get_env_value(root, "HOME"));
	prompt = NULL;
	if (ft_strncmp(get_env_value(root, "PWD"), get_env_value(root, "HOME"), size) == 0)
	{
		prompt = ft_strjoin_gnl(prompt, "\033[1m\033[32m");
		prompt = ft_strjoin_gnl(prompt, get_env_value(root, "USER"));
		prompt = ft_strjoin_gnl(prompt, "@miniteam:\033[1m\033[34m~");
		prompt = ft_strjoin_gnl(prompt, get_env_value(root, "PWD") + size);
	}
	else
	{
		prompt = ft_strjoin_gnl(prompt, "\033[1m\033[32m");
		prompt = ft_strjoin_gnl(prompt, get_env_value(root, "USER"));
		prompt = ft_strjoin_gnl(prompt, "@miniteam:\033[1m\033[34m~");
		prompt = ft_strjoin_gnl(prompt, get_env_value(root, "PWD"));
	}
	prompt = ft_strjoin_gnl(prompt, "\033[0m$ ");
	return(prompt);
}
