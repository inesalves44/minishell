/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:58:38 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/04 16:03:46 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexical_node(char *str, int i, int j)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (node)
	{
		if (str)
			node->str = ft_strdup(str);
		else
			node->str = NULL;
		node->type = i;
		node->number = j;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

int	check_signal(char *main, int *i, t_lexer **node)
{
	int	j;

	j = *i;
	if (main[j] == '|')
	{
		if (j == 0)
			return (error_syntax(&main[j], 2));
		else
			*node = lexical_node(NULL, pipem, j);
		*i = j;
	}
	else if (main[j] == '<')
	{
		if (main[j + 1] == '<')
		{
			*node = lexical_node(NULL, here_doc, j);
			j++;
		}
		else
			*node = lexical_node(NULL, red_in, j);
		*i = j;
	}
	else if (main[j] == '>')
	{
		if (main[j + 1] == '>')
		{
			*node = lexical_node(NULL, app_out, j);
			j++;
		}
		else
			*node = lexical_node(NULL, red_out, j);
		*i = j;
	}
	return (0);
}

char	*treating_quotes(char *str, char s, int *b)
{
	int		i;
	int		j;
	int		a;
	int		len;
	char	*test;

	j = *b;
	i = j + 1;
	while (str[i] != s)
		i++;
	len = i - j;
	test = (char *)malloc(sizeof(char) * (len));
	a = 0;
	while (a < len - 1)
	{
		test[a] = str[j + 1];
		a++;
		j++;
	}
	test[a] = '\0';
	*b = i;
	return (test);
}

char	*treating_str1(char *main, int i, int j)
{
	char	*str;
	int		a;
	int		len;

	a = 0;
	len = j - i;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (a < len)
	{
		str[a] = main[i];
		a++;
		i++;
	}
	str[a] = '\0';
	return (str);
}

int	check_firstnode(char *main, int *i, t_lexer **node)
{
	int		j;
	int		a;
	char	*test;

	j = 0;
	if (check_signal(main,  &j, node))
		return (2);
	if (*node != NULL)
	{
		*i = j;
		return (0);
	}
	if (main[j] == 34 || main[j] == 39)
	{
		test = treating_quotes(main, main[j], &j);
		*node = lexical_node(test, main[j] + '0', j);
		*i = j;
		return (0);
	}
	a = 0;
	while (main[j] != '\0' && main[j] != ' ' && main[j] != '<' && main[j] != '>' && main[j] != '|')
		j++;
	test = treating_str1(main, a ,j);
	*node = lexical_node(test, 0, a);
	*i = j - 1;
	return (0);
}

int	lexical_annalysis(t_lexer **node, char *str)
{
	char	*test;
	int		i;
	int		j;

	i = 0;
	j = 0;
	*node = NULL;
	if (check_firstnode(str, &i, node))
		return (2);
	i++;
	while (str[i] != '\0')
	{
		j = i;
		if (check_signal(str, &i, &(*node)->next))
			return (2);
		if (!(*node)->next && str[i] != ' ')
		{
			if ((str[i] == 34 || str[i] == 39))
			{
				test = treating_quotes(str, str[i], &i);
				(*node)->next = lexical_node(test, str[j] + '0', j);
			}
			else
			{
				while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '|')
					i++;
				test = treating_str1(str, j, i);
				i--;
				(*node)->next = lexical_node(test, 0, j);
			}
			free (test);
		}
		if ((*node)->next)
		{
			(*node)->next->prev = *node;
			*node = (*node)->next;
		}
		i++;
	}
	while ((*node)->prev)
		*node = (*node)->prev;
	int	a = 0;
	while (*node)
	{
		(*node)->number = a;
		if (!(*node)->next)
			break ;
		*node = (*node)->next;
		a++;
	}
	while ((*node)->prev)
		*node = (*node)->prev;
	/*int test2 = 1;
	while (*node)
	{
		printf("------------number: %d-----------\n", (*node)->number);
		printf("value of node: %d\n", (*node)->type);
		if ((*node)->str)
			printf("string of the node: %s\n", (*node)->str);
		test2++;
		if (!(*node)->next)
			break ;
		(*node) = (*node)->next;
	}
	while ((*node)->prev)
		(*node) = (*node)->prev;*/
	return (0);
}
