/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:38:09 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/18 18:01:06 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_file(t_root *root)
{
	char	*buf;

	if (root->tree->type == red_in)
		root->in = open(root->tree->left->file, O_RDONLY);
	else
		root->in = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (root->in < 0)
		return (error_process(": no such file or directory", root->tree->left, 1));
	if (root->tree->type == here_doc)
	{
		while (1)
		{
			write(1, ">", 1);
			buf = get_next_line(0);
			write(root->in, buf, ft_strlen(buf));
			if (ft_strlen(buf) == (ft_strlen(root->tree->left->file) + 1) && \
				!ft_strncmp(buf, root->tree->left->file, ft_strlen(root->tree->left->file)))
				break ;
			free(buf);
		}
		root->in = open(".here_doc", O_RDONLY);
		if (root->in < 0)
			return (error_process(": no such file or directory", root->tree->left, 1));
	}
	return (0);
}

int	output_file(t_root *root)
{
	if (root->tree->type == red_out)
		root->out = open(root->tree->left->file, O_CREAT | O_TRUNC | O_RDWR, 0000666);
	else
		root->out = open(root->tree->left->file, O_APPEND | O_CREAT | O_RDWR, 0000666);
	if (root->out < 0)
		return (error_process(": no such file or directory", root->tree->left, 1));
	return (0);
}

int	checking_redirects(t_root *root, int *status)
{
	while (root->tree)
	{
		if (root->tree->type == red_in || root->tree->type == here_doc)
			*status = input_file(root);
		else if (root->tree->type == red_out || root->tree->type == app_out)
			*status = output_file(root);
		else if (root->tree->type == pipem || root->tree->type == command)
			break ;
		if (!root->tree->rigth)
			break ;
		if (*status != 0)
			return (*status);
		root->tree = root->tree->rigth;
	}
	return (0);
}