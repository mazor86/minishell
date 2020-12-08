/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_begin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 19:32:45 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/08 19:33:29 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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