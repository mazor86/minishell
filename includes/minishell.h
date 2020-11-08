/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/08 20:54:07 by tisabel          ###   ########.fr       */
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

# define BUFFER_SIZE 1024

typedef struct	s_all
{
	
}				t_all;

/*
** name = name of the command
** flag = if there are any flags in the command
** argum = argunents of the command
** tail = if there is something left in the read line
** 
*/

typedef struct		s_data
{
	char			*name;
	char			*flag;
	char			**argum;
	char			*tail;
}					t_data;

/*
typedef struct		s_list
{
	t_data			*content;
	struct s_list	*next;
}					t_list;*/
	
/*
** Basic functions
*/

int				get_next_line(int fd, char **line);
char			*ft_strcut(char *str, char c);
void			init_data(t_data *data);
int 			new_arg(char ***array, char *new_arg);
void    		free_array(char ***array);

/*
** Parser functions
*/

int				parce_command(t_list **command, char *line, char **my_env);
int				parce_line(t_list **command, char *line, char **my_env);
void			ft_check_name(t_list **command, char **my_env);
int				ft_parce_s_quotes(char *line, t_data *data, char **my_env);
int				ft_parce_d_quotes(char *line, t_data *data, char **my_env);

/*
** Error treatment functions
*/

void    		ft_wrong_command(t_list **command, char **my_env);

int				start_cmd(t_list *lst);

#endif
