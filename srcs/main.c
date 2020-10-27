/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/10/27 17:28:03 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

int		main(int args, char **argv, char **env)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	char	*line;
	
	(void)args;
	(void)argv;
	for (size_t i = 0; env[i]; i++)
	{
		printf("%s\n", env[i]);
	}
	
	while ((ret = read(0, buf, BUFFER_SIZE)) > 0)
	{
		get_next_line(ret, &line);
		printf("%s", line);
	}
	return (0);
}
