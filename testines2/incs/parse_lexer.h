/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:21:16 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/22 13:49:09 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LEXER_H
# define PARSE_LEXER_H

# include "../minishell.h"
# include "lists_structs.h"

/*==============parsing=========================================*/
/*parsing.c*/
int     first_objects(t_lexer **lexer, t_ast **tree);
int     when_pipe(t_lexer **lexer, t_ast **tree);
void	finish_parse(t_lexer **lexer, t_ast **tree);
int     second_loop(t_lexer **l, t_ast **t);
int     parsing_str(t_lexer **l, t_ast **t);
/*parsing utils*/
int     get_file(t_lexer **lexer, t_ast *node);
int     pipes_lexer(t_lexer *lexer);
int     length_lexer(t_lexer *lexer, t_ast *aux, int i);
char	**newstring(t_lexer **lexer, t_ast **tree);
char	**treat_string(t_lexer **lexer, t_ast **aux, t_ast **tree);
void	print_tree(t_ast *node, int i);
/*parsing uitls2*/
int     check_nodespart2(t_ast *tree, t_lexer *lexer, int red);
int     checking_nodes(t_ast *tree, t_lexer *lexer, int i);
int     is_file(int i);
void	array_quotes(t_ast **tree, t_lexer **lexer, int j);
char	**create_array(t_lexer **lexer, int len, t_ast **tree);
/*parsing utils 3*/
void    find_filecomand(t_lexer **lexer, t_ast **aux, int check, t_ast **node);
t_ast   *create_treenode(t_lexer **lexer, t_ast **aux, int check);
void    passing_file(t_lexer **lexer);
int     leftnode_file(t_lexer **lexer, t_ast **tree, int i);
int     when_file(t_lexer **lexer, t_ast **tree);


/*===================lexical=====================================*/
t_lexer		*lexical_node(char *str, int i, int j);
int			endofquotes(char s);
int			endofstring(char s);
int			node_type(t_lexer *node, char s);
int			closing_q(char *str, char c, int i, int *a);
int			check_signal1(char *main, int *i, t_lexer **node);
int			check_signal(char *main, int *i, t_lexer **node);
char		*treating_quotes(char *str, char s, int *b);
int			lexical_annalysis(t_lexer **node, char *str);
char		*create_string(char *line);
int			closing_q2(char *str, char c, int i, int len);

#endif
