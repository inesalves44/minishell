/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:47:57 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/02 21:57:06 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_error(const char *arg)
{
	int		i;

	i = -1;
	if (arg[0] == '$')
	{
			ft_putstr_fd("minishell: export: `", STDERR);
			while(arg[++i])
				write(STDERR, &arg[i], 1);
			ft_putstr_fd("\': not a valid identifier\n", STDERR);
			return (TRUE);
	}
	else if (ft_strchr(arg, '=') == NULL)
	{
		ft_putstr_fd("\n", STDERR);
		return (TRUE);
	}
	return (FALSE);
}


int	change_value(t_root *root, char *key, char *new_value)
{
	t_envlst	*head;

	head = root->my_envp.env_lst;
	while(root->my_envp.env_lst)
	{
		if (ft_strncmp(key, root->my_envp.env_lst->key, ft_strlen(key)) == 0)
		{
			free(root->my_envp.env_lst->value);
			//free(root->my_envp.env_lst->key);
			//root->my_envp.env_lst->key = key;
			root->my_envp.env_lst->value = new_value;
			root->my_envp.env_lst = head;
			return (1);
		}
		root->my_envp.env_lst = root->my_envp.env_lst->next;
	}
	root->my_envp.env_lst = head;
	refresh_env_array(root);
	return (0);
}

void	export(t_root *root)
{
	char	*key;
	char	*value;
	int		param;

	param = 1;
	while (root->ast_tree.command[param])
	{
		if (has_error(root->ast_tree.command[param]))
			break ;
		else
		{
			key = extract_key(root->ast_tree.command[1]);
			value = extract_value(root->ast_tree.command[1]);
			if (!change_value(root, key, value))
			{
				ft_lstadd_back_env(&root->my_envp.env_lst, ft_lstnew_env(key,value));
			}
		}
		param++;
	}
	refresh_env_array(root);
}
