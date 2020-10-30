/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2020/10/30 16:30:00 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

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

typedef struct		s_data
{
	char			*name;
	char			*flag;
	char			*argum;
	char			*tail;
}					t_data;

typedef struct		s_list
{
	t_data			*content;
	struct s_list	*next;
}					t_list;

int				get_next_line(int fd, char **line);
int				parce_line(t_list **command, char *line);
char			*ft_strcut(char *str, char c);
void			init_data(t_data *data);

int				start_cmd(t_list *lst);

#endif
