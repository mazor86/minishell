/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:39:07 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/02 12:54:08 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_echo(t_data *data)
{
	int		i;
	char	flag;

	i = -1;
	is_n = 0;
	while (data->argum[++i])
	{
		if (i == 0 && !ft_strncmp(cmd->argv[i], "-n", 3))
			flag = 1;
		else
		{
			ft_putstr_fd(cmd->argv[i], 1);
			if (cmd->argv[i + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	all->res = 0;
	return (0);
}
