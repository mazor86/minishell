/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/11/09 22:09:54 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void init_struct(t_data *data)
{
	data->name = NULL;
	data->argum = NULL;
	data->tail = NULL;
	data->pipe = 0;
	data->semicolon = 0;
}

int		main(int args, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	
	(void)args;
	(void)argv;
	line = NULL;
	init_struct(&data);
	ft_putstr_fd("bash-3.2$", 0);
	while (get_next_line(0, &line) > 0)
	{
		ft_putstr_fd("bash-3.2$", 0);
		parce_command(&data, line, &envp);
		check_name(&data, &envp);
		free(line);
		line = NULL;
	}
	return (0);
}
