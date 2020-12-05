/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:39:07 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/05 23:36:45 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_data *data, t_var **my_env)
{
	int		i;
	char	is_n;

	i = -1;
	is_n = 0;
	(void)my_env;
	while (data->argum[++i])
	{
		if (!ft_strncmp(data->argum[i], "-n", 3) && !i)
			is_n = 1;
		else
		{
			ft_putstr_fd(data->argum[i], 1);
			if (data->argum[i + 1])
				ft_putchar_fd(' ', 1);
			else if (!data->argum[i + 1] && !is_n)
				ft_putchar_fd('\n', 1);
		}
	}
	return (0);
}
