/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/08 17:56:04 by tisabel          ###   ########.fr       */
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
** global variable for exit status
*/

int				g_exit_status = 0;

/*
** General functions for reading input and processing arguments and variables
*/

char			*ft_strcut(char *str, char c);
int 			new_arg(char ***array, char *new_arg);
char            **copy_array(char **array);
int             check_digit(char *str);


/*
** General functions for reading input and processing arguments and variables
*/

int				clear_all(t_all *all);
char			**deconvert_env(t_all *all);
char			**convert_argv(t_cmd *lst);
char			*get_full_cmd_name(t_all *all, t_cmd *lst);
int            	set_var(char *line, t_env **my_env);
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


/*
** Cmd utils functions
*/

t_cmd			*cmdlast(t_cmd *lst);
void			cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd			*init_cmd(void);
int				is_null_cmd(t_cmd *lst);
void			clear_cmd(t_cmd **cmd_lst);

/*
** Env utils functions
*/

t_env			*copy_env(t_env *my_env);
int				count_var(t_env *var);
void			sort_env(t_env *var);
void			free_t_env(t_env **my_env);
int				change_env(t_env *my_env, char *var_name, char *new_value);

void			convert_envp(t_env **envp_var, char **envp);
int				parser_env(t_all *all, char **env);
t_env			*get_env(t_all *all, char *name);
char			*get_name_env(char *env);
char			*get_param_env(char *env);
int				add_env(t_all *all, char *name, char *par);
void			sort_env(t_env *var);

/*
** buildin functions
*/

int				ft_echo(t_all **all);
int				ft_pwd(t_all **all);
int				ft_export(t_all **all);
int				ft_env(t_all **all);
int				ft_unset(t_all **all);
int				ft_cd(t_all **all);
int				ft_exit(t_all **all);

int				join_char(char **text, char c);
int				join_str(char **text, char *s);
void			trim_space(t_all *all);
char			**remalloc_args(char **args);
int				add_remalloc_argv(t_all *all, const char *spec, int *i);
void			*free_array(char **text);

/*
** errors processing functions
*/

int				ft_error(char *name, char *text, int ret, char *var);
//void    		exec_commands(t_data *data, char *line, t_env **my_env);
//int				parce_command(t_data *data, char *line, t_env **my_env);
//void			parce_line(t_data *data, char *line, t_env **my_env);
//void			check_name(t_data *data, char ***my_env);
//int				parce_s_quotes(char *line, t_data *data, t_env **my_env);
//int				parce_d_quotes(char *line, t_data *data, t_env **my_env);

//int             get_ecran(char *line, t_data *data, t_env **my_env);
//int             get_arg(char *line, t_data *data, t_env **my_env);
//int             exec_pipe(char *line, t_data *data, t_env **my_env);
//int             exec_semicolon(char *line, t_data *data, t_env **my_env);

#endif
