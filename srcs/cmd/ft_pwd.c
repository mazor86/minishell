/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:43:41 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/08 22:17:00 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_data *data, t_var **my_env)
{
	int i;

	i = 0;
	if(data->argum[0] != 0)
	{
		write(1, "Error. Wrong number of arguments.", 34);
		g_exit_status = 2;
		exit(g_exit_status);
	}
	else
	{
		while (ft_strncmp((*my_env)[i].name, "PWD") != 0)
			i++;
		write(1, (*my_env)[i].value, ft_strlen((*my_env)[i].value));
		write(1, "\n", 1);
	}
	return (0);
}
