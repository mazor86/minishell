/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 13:35:15 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/05 23:34:53 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

static void init_struct(t_data *data)
{
	data->name = NULL;
	data->argum = NULL;
	data->pipe = 0;
	data->semicolon = 0;
}

void	convert_envp(t_var **envp_var, char **envp)
{
	int i;
	int j;
	int len_envp;

	i = 0;
	len_envp = 0;
	while (envp[len_envp])
		len_envp++;
	if (!(*envp_var = (t_var*)malloc(sizeof(t_var) * (len_envp + 1))))
		exit (1);
	while (envp[i] != NULL)
	{
		j = 0;
		(*envp_var)[i].name = ft_strcut(envp[i], '=');
		while (envp[i][j] != '=')
			j++;
		(*envp_var)[i].value = ft_strdup(&envp[i][j + 1]);
		i++;
	}
	(*envp_var)[i].name = NULL;
}

void    exec_commands(t_data *data, char *line, t_var **my_env)
{
	if (line[0] == '\0')
		{
			g_exit_status = 0;
			return ;
		}
    parce_command(data, line, my_env);
    check_name(data, my_env);
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
		printf("Input line: %s$\n", line);
		init_struct(&data);
		ft_putstr_fd("bash-3.2$ ", 0);
		exec_commands(&data, line, &envp_var);
		free(line);
		line = NULL;
	}
	return (0);
}
