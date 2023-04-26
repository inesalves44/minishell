/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:25:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/20 17:30:14 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dq_print(t_root *root, char *cmd);
int	is_valid_param(char *cmd);

static int	get_end(char *cmd, int dquote)
{
	size_t	end;

	end = 0;
	while (cmd[end] != ' ' && cmd[end] != '$' && cmd[end])
		end++;
	if (cmd[end - 1] == '\'' && dquote != -1)
		return (end - 1);
	return (end);
}

static int	handler_env(t_root *root, char *begin, size_t end)
{
	char	*value;
	char	*key;

	key = ft_calloc(sizeof(char), end + 1);
	ft_strlcpy(key, begin, end + 1);
	value = get_env_value(root, key);
	free(key);
	if (value)
	{
		ft_putstr_fd(value, root->out);
		free(value);
	}
	return (end);
}

static int	do_print_echo(t_root *root, char *cmd, int dquote)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while (i < ft_strlen(cmd))
	{
		if (cmd[i] == '$' && cmd[i + 1])
		{
			i++;
			end = get_end(cmd + i, dquote);
			i += handler_env(root, cmd + i, end);
		}
		else
		{
			ft_putchar_fd(cmd[i], root->out);
			i++;
		}
	}
	return (1);
}

static int	loop_echo(t_root *root)
{
	int	cmd;
	int	space;

	space = 0;
	cmd = 1;
	while (is_valid_param(root->tree->command[cmd]) && root->tree->command[cmd])
			cmd++;
	while (root->tree->command[cmd])
	{
		if (root->tree->squotes[cmd] != -1)
			space = dq_print(root, root->tree->command[cmd]);
		else
			space = do_print_echo(root, root->tree->command[cmd], \
			root->tree->dquotes[cmd]);
		cmd++;
		if (root->tree->command[cmd] && space == 1)
			ft_putchar_fd(' ', root->out);
		space = 0;
	}
	if (!is_valid_param(root->tree->command[1]))
		ft_putchar_fd('\n', root->out);
	return (0);
}

int	echo(t_root *root)
{
	if (get_array_size(root->tree->command) <= 1)
		ft_putchar_fd('\n', root->out);
	else
		loop_echo(root);
	return (0);
}