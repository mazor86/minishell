/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/10/30 16:27:12 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

int		main(int args, char **argv, char **env)
{
	t_data	all;
	char	*line;
	
	(void)args;
	(void)argv;
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	return (0);
}
