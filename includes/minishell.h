/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/11 11:42:21 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "struct.h"

/*
** General functions for reading input and processing arguments and variables
*/

char			*ft_strcut(char *str, char c);
int             check_digit(char *str);
int				clear_all(t_all *all);
char			**deconvert_env(t_all *all);
char			**convert_argv(t_cmd *lst);
char			*get_full_cmd_name(t_all *all, t_cmd *lst);
char            *get_var(t_env *my_env, char *var_name);

/*
** Parcer functions
*/

int				parser_string(t_all *all);
int				get_shielding(t_all *all, char **text);
int				get_variables(t_all *all, char **text);
int				get_strong_quotes(t_all *all, char **text);
int				get_quotes(t_all *all, char **text);
int				parser_cmd(t_all *all);
int				parser_syntax_errors(t_all *all);
int				start_cmd(t_all *all, t_cmd *lst);
int				start_execve(t_all *all, t_cmd *lst, char **envp,
					char **argv);


/*
** Cmd utils functions
*/

t_cmd			*cmdlast(t_cmd *lst);
void			cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd			*init_cmd(void);
int				is_null_cmd(t_cmd *lst);
void			clear_cmd(t_cmd **cmd_lst);
int 			cmd_len(t_cmd *cmd);

/*
** Env utils functions
*/

t_env			*init_env(void);
t_env			*copy_env(t_env *my_env);
int				count_env(t_env *my_env);
void			sort_env(t_env **my_env);
void			free_t_env(t_env **my_env);
int				change_env(t_all *all, char *var_name, char *new_value);
void			del_one_env(t_env *my_env);
int				convert_env(t_env **env_var, char **env, t_all *all);
t_env			*env_last(t_env *env);
void			add_arg(char *argum, t_env **my_env);

/*
** buildin functions
*/

int				ft_echo(t_all *all, t_cmd *cmd);
int				ft_pwd(t_all *all, t_cmd *cmd);
int				ft_export(t_all *all, t_cmd *cmd);
int				ft_env(t_all *all, t_cmd *cmd);
int				ft_unset(t_all *all, t_cmd *cmd);
int				ft_cd(t_all *all, t_cmd *cmd);
int				ft_exit(t_all *all, t_cmd *cmd);

/*
** execve functions
*/

int				join_char(char **text, char c);
int				join_str(char **text, char *s);
void			trim_space(t_all *all);
char			**remalloc_args(char **args);
int				add_remalloc_argv(t_all *all, const char *spec, int *i);
void			*free_array(char **text);

/*
** errors processing functions
*/

int				ft_error(char *name, char *text, int ret, t_all *all);

/*
** Pipe functions
*/

int				with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp);
void			save_fds(t_all *all);

#endif
