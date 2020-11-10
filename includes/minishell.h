/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 21:32:14 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h> //
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include "struct.h"

# define BUFFER_SIZE 1024

extern int g_exit_status;

/*
** Basic functions
*/

int				get_next_line(int fd, char **line);
char			*ft_strcut(char *str, char c);
void			init_data(t_data *data);
int 			new_arg(char ***array, char *new_arg);
void    		free_array(char ***array);
char            **copy_array(char **array);
int             check_digit(char *str);

/*
** Parser functions
*/

int				parce_command(t_data *data, char *line, char ***my_env);
void			parce_line(t_data *data, char *line, char ***my_env);
void			check_name(t_data *data, char ***my_env);
int				parce_s_quotes(char *line, t_data *data, char ***my_env);
int				parce_d_quotes(char *line, t_data *data, char ***my_env);
int             set_var(char *line, t_data *data, char ***my_env);
int             get_var(char *line, t_data *data, char ***my_env);
int             get_ecran(char *line, t_data *data, char ***my_env);
int             get_arg(char *line, t_data *data, char ***my_env);
int             exec_pipe(char *line, t_data *data, char ***my_env);
int             exec_semicolon(char *line, t_data *data, char ***my_env);

/*
** Remaked functions
*/

int				ft_cd(t_data *data, char ***my_env);
int				ft_echo(t_data *data, char ***my_env);
int				ft_env(t_data *data, char ***my_env);
int				ft_exit(t_data *data, char ***my_env);
int				ft_export(t_data *data, char ***my_env);
int				ft_pwd(t_data *data, char ***my_env);
int				ft_unset(t_data *data, char ***my_env);

/*
** Exit, error and free functions
*/

void    		wrong_command(t_data *data, char ***my_env);
void	        free_struct(t_data *data);

int				start_cmd(t_list *lst);

#endif
