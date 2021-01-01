/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:48:51 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/31 02:52:14 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_data *data, t_var **my_env)
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
		while ((*my_env)[i].name != NULL)
		{
			if ((*my_env)[i].standard == 1)
			{
				write(1, (*my_env)[i].name, ft_strlen((*my_env)[i].name));
				write(1, "=", 1);
				write(1, (*my_env)[i].value, ft_strlen((*my_env)[i].value));
				write(1, "\n", 1);
			}
		i++;
		}
	return (0);
}
