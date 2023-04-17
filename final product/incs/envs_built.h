/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_built.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:08:36 by hmaciel-          #+#    #+#             */
/*   Updated: 2023/04/17 15:20:46 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVS_BUILT_H
# define ENVS_BUILT_H

# include "../minishell.h"

# define TRUE 1
# define FALSE 0
# define BUFFER_PATH 4000

/* env funcs*/

void		init_envp(t_root *root, char **envp);
void		print_envlsts(t_root *root);
void		ft_lstadd_back_env(t_envlst **envs, t_envlst *new);
t_envlst	*ft_lstlast_envlst(t_envlst *envs);
t_envlst	*ft_lstnew_env(char *key, char *value);
void		free_envp_lst(t_root *root);
void		free_envp_array(t_root *root);
void		refresh_env_array(t_root *root);
int			get_array_size(char **array);
int			get_lst_size(t_envlst *lst);
char		*ft_strjoin_gnl(char *s1, char *s2);
int			print_env_value(t_root *root, char *key);
char		*get_env_value(t_root *root, char *key);
int			change_value(t_root *root, char *key, char *new_value);
char		*get_value_from_str(char *env);
char		*get_key_from_str(char *env);
void		free_array(char **array);
void		free_env_node(t_envlst *node);

/*built in*/
int			built_in_router(t_root *root);
int			cd(t_root *root);
int			echo(t_root *root);
int			pwd(t_root *root);
int			export(t_root *root);
int			unset(t_root *root);
int			env(t_root *root);
int			is_built(char **commands);

#endif