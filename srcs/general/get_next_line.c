/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:01:03 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/26 11:20:44 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int      ft_gnl_exit(t_all *all)
{
    ft_putstr_fd("exit\n", 1);
    free_t_env(&all->my_env);
    clear_all(all);
    exit(all->exit_status);
}

static int		set_read(int fd, char **line, t_all *all)
{
	char	*res;
	int     ret;
	char	buf[2];

	while ((ret = read(fd, buf, 1)) >= 0)
	{
        if (ret == 0)
        {
            if (ft_strcmp(*line, "") == 0)
                ft_gnl_exit(all);
            else
            {
                ft_putstr_fd("  \b\b", 1);
                continue ;
            }
        }
		buf[1] = 0;
		if (buf[0] == '\n')
			break ;
		if (!*line)
		{
			if (!(*line = ft_strdup("")))
				return (-1);
		}
		res = *line;
		if (!(*line = ft_strjoin(res, buf)))
			return (-1);
		free(res);
	}
	return (1);
}

int				get_next_line(int fd, char **line, t_all *all)
{
	if (fd < 0 || !line)
		return (-1);
	if (set_read(fd, line, all) == -1)
		return (-1);
	return (1);
}
