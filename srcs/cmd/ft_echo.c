/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:08:06 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/23 19:03:08 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_echo(t_all *all, t_cmd *cmd)
{
	int		i;
	char	flag;

	i = -1;
	flag = 0;
	while (cmd->argv[++i])
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
