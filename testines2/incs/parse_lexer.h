/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:21:16 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/15 15:28:07 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LEXER_H
# define PARSE_LEXER_H

# include "../minishell.h"
# include "lists_structs.h"

/*parsing*/
int			get_file(t_lexer **lexer, t_ast *node);
int			pipes_lexer(t_lexer *lexer);
int			length_lexer(t_lexer *lexer, t_ast *aux, int i);
char		**treat_string(t_lexer **lexer, t_ast **aux, t_ast **tree);
char		**create_array(t_lexer **lexer, int len, t_ast **tree);
int			is_file(int i);
void		passing_file(t_lexer **lexer);void	passing_file(t_lexer **lexer);
void		array_quotes(t_ast **tree, t_lexer **lexer, int j);
int			parsing_str(t_lexer **l, t_ast **t);
t_ast		*create_treenode(t_lexer **lexer, t_ast **aux, int check);
int			checking_nodes(t_ast *tree, t_lexer *lexer, int i);

/*lexical*/
t_lexer		*lexical_node(char *str, int i, int j);
int			endofquotes(char s);
int			endofstring(char s);
int			node_type(t_lexer *node, char s);
int			closing_q(char *str, char c, int i);
int			check_signal1(char *main, int *i, t_lexer **node);
int			check_signal(char *main, int *i, t_lexer **node);
char		*treating_quotes(char *str, char s, int *b);
int			lexical_annalysis(t_lexer **node, char *str);

#endif