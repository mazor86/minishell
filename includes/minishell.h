/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 18:23:59 by tisabel          ###   ########.fr       */
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
	
/*
** Basic functions
*/

int				get_next_line(int fd, char **line);
char			*ft_strcut(char *str, char c);
void			init_data(t_data *data);
int 			new_arg(char ***array, char *new_arg);
void    		free_array(char ***array);
char            **copy_array(char **array);

/*
** Parser functions
*/

int				parce_command(t_list **command, char *line, char ***my_env);
void			parce_line(t_list **command, char *line, char ***my_env);
void			check_name(t_list **command, char ***my_env);
int				parce_s_quotes(char *line, t_data *data, char ***my_env);
int				parce_d_quotes(char *line, t_data *data, char ***my_env);

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
** Error treatment functions
*/

void    		wrong_command(t_list **command, char ***my_env);

int				start_cmd(t_list *lst);

#endif
