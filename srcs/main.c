/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/08 19:49:16 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_struct(t_data *data)
{
	data->name = NULL;
	data->argum = NULL;
	data->pipe = 0;
	data->semicolon = 0;
}

int		main(int args, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	t_var	*envp_var;
	
	(void)args;
	(void)argv;
	line = NULL;
	g_exit_status = 0;
	data.tail = NULL;
	convert_envp(&envp_var, envp);
	ft_putstr_fd("bash-3.2$ ", 0);
	while (get_next_line(0, &line))
	{
		init_struct(&data);
		ft_putstr_fd("bash-3.2$ ", 0);
		exec_commands(&data, line, &envp_var);
		free(line);
		line = NULL;
	}
	return (0);
}
