/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/02 13:20:25 by tisabel          ###   ########.fr       */
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

int				get_next_line(int fd, char **line);
char			*ft_strcut(char *str, char c);
void			init_data(t_data *data);
int 			new_arg(char ***array, char *new_arg);
void    		free_array(char ***array);
char            **copy_array(char **array);
int             check_digit(char *str);
void			convert_envp(t_var **envp_var, char **envp);

int				parser_env(t_all *all, char **env);
t_env			*get_env(t_all *all, char *name);
char			*get_name_env(char *env);
char			*get_param_env(char *env);
int				add_env(t_all *all, char *name, char *par);
int				update_env(t_all *all, char *name, char *txt, char is_created);
t_list			*sort_env(t_list *lst);
int				free_env(t_env **tmp, t_list **lst);
void			clear_env(t_list **lst);
int				clear_all(t_all *all);
char			**convert_env(t_all *all);
char			**convert_argv(t_list *lst);
char			*get_full_cmd_name(t_all *all, t_list *lst);

int				parser_string(t_all *all);
int				get_shielding(t_all *all, char **text);
int				get_variables(t_all *all, char **text);
int				get_strong_quotes(t_all *all, char **text);
int				get_quotes(t_all *all, char **text);
int				parser_cmd(t_all *all);
int				parser_syntax_errors(t_all *all);

int				ft_echo(t_all *all, t_cmd *cmd);
int				ft_pwd(t_all *all, t_cmd *cmd);
int				ft_export(t_all *all, t_cmd *cmd);
int				ft_env(t_all *all, t_cmd *cmd);
int				ft_unset(t_all *all, t_cmd *cmd);
int				ft_cd(t_all *all, t_cmd *cmd);
int				ft_exit(t_all *all, t_cmd *cmd);

t_cmd			*init_cmd(void);
int				is_null_cmd(t_list *lst);
void			clear_cmd(t_cmd **cmd_lst);
void			free_t_var(t_var **my_env);
int				start_cmd(t_list *lst);

int				join_char(char **text, char c);
int				join_str(char **text, char *s);
void			trim_space(t_all *all);
char			**remalloc_args(char **args);
int				add_remalloc_argv(t_all *all, const char *spec, int *i);
void			*free_split(char **text);

int				ft_error(char *name, char *text, int ret);
void    		exec_commands(t_data *data, char *line, t_var **my_env);
int				parce_command(t_data *data, char *line, t_var **my_env);
void			parce_line(t_data *data, char *line, t_var **my_env);
void			check_name(t_data *data, char ***my_env);
int				parce_s_quotes(char *line, t_data *data, t_var **my_env);
int				parce_d_quotes(char *line, t_data *data, t_var **my_env);
void            set_var(char *line, t_var **my_env);
int             get_var(t_var **my_env, char *var_name);
int             get_ecran(char *line, t_data *data, t_var **my_env);
int             get_arg(char *line, t_data *data, t_var **my_env);
int             exec_pipe(char *line, t_data *data, t_var **my_env);
int             exec_semicolon(char *line, t_data *data, t_var **my_env);

#endif
