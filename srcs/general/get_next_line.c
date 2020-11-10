/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:41:23 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/07 18:27:20 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** Frees the pointers.
*/

static int	ft_clean(char **ptr1, char **ptr2, short i)
{
	if (i < 0 || i > 2 || !(*ptr1))
		return (-1);
	free(*ptr1);
	*ptr1 = NULL;
	ptr1 = NULL;
	if (i == 2)
	{
		if (!(*ptr2))
			return (-1);
		free(*ptr2);
		*ptr2 = NULL;
		ptr2 = NULL;
	}
	return (-1);
}

/*
** Writes string till \n into line and
** the rest to the static variable.
*/

static int	ft_write_line(char **tail, char **line, char *ptr_tail)
{
	char *temp;

	ptr_tail[0] = '\0';
	ptr_tail++;
	if (!(*line = ft_strdup(*tail)))
		return (ft_clean(tail, NULL, 1));
	if (ptr_tail == NULL)
	{
		ft_clean(tail, NULL, 1);
		return (1);
	}
	temp = ft_strdup(ptr_tail);
	free(*tail);
	*tail = temp;
	return (1);
}

/*
** Writes the last line.
*/

static int	ft_last_line(char **tail, char **line, char **buf)
{
	if (*tail)
		if (!(*line = ft_strjoin(*line, *tail)))
			return (ft_clean(buf, tail, 2));
	ft_clean(buf, tail, 2);
	return (0);
}

/*
** Reads the text from file and processes it to line and tail.
*/

static int	ft_read_text(char **tail, char **line, int fd)
{
	ssize_t read_num;
	char	*buf;
	char	*ptr_tail;

	buf = NULL;
	if (!(buf = (char*)(malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while ((read_num = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_num] = '\0';
		if (!(*tail = ft_strjoin(*tail, buf)))
			return (ft_clean(&buf, tail, 2));
		if ((ptr_tail = ft_strchr(*tail, '\n')))
		{
			free(buf);
			return (ft_write_line(tail, line, ptr_tail));
		}
	}
	if (!(*line = ft_strdup("")))
		return (ft_clean(tail, &buf, 2));
	return (ft_last_line(tail, line, &buf));
}

/*
** Operates with remaining read part of the buffer and processes it to line.
** Launches the reading from file if all the string tail remaining
** in memory was printed.
*/

int			get_next_line(int fd, char **line)
{
	static char	*tail[12000];
	char		*ptr_tail;

	ptr_tail = NULL;
	if (fd < 0 || fd > 12000 || !line || BUFFER_SIZE <= 0
		|| read(fd, NULL, 0) == -1)
		return (-1);
	if (tail[fd])
	{
		if ((ptr_tail = ft_strchr(tail[fd], '\n')))
			return (ft_write_line(&tail[fd], line, ptr_tail));
	}
	return (ft_read_text(&tail[fd], line, fd));
}
