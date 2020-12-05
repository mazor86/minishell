/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_semic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:54:00 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/05 22:23:52 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_semicolon(char *line, t_data *data, char ***my_env)
{
	(void)data;
	(void)my_env;
	(void)line;
	data->semicolon = 1;
	new_arg(&(data->argum), ft_strcut(line, ';'));
	free_struct(data);
	return (0);
}

int	exec_pipe(char *line, t_data *data, char ***my_env)
{
	(void)data;
	(void)my_env;
	(void)line;
	data->pipe = 1;
	new_arg(&(data->argum), ft_strcut(line, '|'));
	return (0);
}