/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:39:07 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/05 12:02:52 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_echo(t_all **all)
{
	int		i;
	int		is_n;
	char	flag;

	i = -1;
	is_n = 0;
	while ((*all)->cmd->argv[++i])
	{
		if (i == 0 && !ft_strncmp((*all)->cmd->argv[i], "-n", 3))
			flag = 1;
		else
		{
			ft_putstr_fd((*all)->cmd->argv[i], 1);
			if ((*all)->cmd->argv[i + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
	return (0);
}
