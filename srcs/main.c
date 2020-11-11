/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/11/11 20:48:12 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

static void init_struct(t_data *data)
{
	data->name = NULL;
	data->argum = NULL;
	data->tail = NULL;
	data->pipe = 0;
	data->semicolon = 0;
}

void    exec_commands(t_data *data, char *line, char ***my_env)
{
    parce_command(data, line, my_env);
    check_name(data, my_env);
}

int		main(int args, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	
	(void)args;
	(void)argv;
	line = NULL;
	g_exit_status = 0;
	init_struct(&data);
	ft_putstr_fd("bash-3.2$ ", 0);
	while (get_next_line(0, &line))
	{
		ft_putstr_fd("bash-3.2$ ", 0);
		exec_commands(&data, line, &envp);
		free(line);
		line = NULL;
	}
	return (0);
}
