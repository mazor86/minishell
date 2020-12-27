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

#include "libft.h"

static int		set_read(int fd, char **line)
{
	char	*res;
	char	buf[2];

	while (read(fd, buf, 1) > 0)
	{
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
	return (0);
}

int				get_next_line(int fd, char **line)
{
	if (fd < 0 || !line)
		return (-1);
	if (set_read(fd, line) == -1)
		return (-1);
	return (1);
}
