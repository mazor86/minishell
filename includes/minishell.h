/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:05:41 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/27 21:45:33 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef struct	s_env
{
	char	*name;
	char	*par;
}				t_env;

typedef struct	s_cmd
{
	char	*name;
	char	**argv;
	char	pipe_start;
	char	pipe_end;
}				t_cmd;

typedef struct	s_all
{
	t_list	*env;
	t_list	*cmd;
	char	*line;
	int		pos;
	int		res;
}				t_all;

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

int				ft_echo(t_all *all, t_cmd *cmd);
int				ft_pwd(t_all *all, t_cmd *cmd);
int				ft_export(t_all *all, t_cmd *cmd);
int				ft_env(t_all *all, t_cmd *cmd);
int				ft_unset(t_all *all, t_cmd *cmd);
int				ft_cd(t_all *all, t_cmd *cmd);
int				ft_exit(t_all *all, t_cmd *cmd);

t_list			*init_cmd(void);
void			clear_cmd(t_list **lst);

int				join_char(char **text, char c);
int				join_str(char **text, char *s);
void			trim_space(t_all *all);
char			**remalloc_args(char **args);
int				add_remalloc_argv(t_all *all, const char *spec, int *i);
void			*free_split(char **text);

int				ft_error(char *name, char *text, int ret);

#endif
