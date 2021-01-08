/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:38:00 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 17:48:46 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

/*
** executes the exit command
**
** @param *all general structure
** @param *cmd command structure
** @return 0
*/

int		ft_exit(t_all **all)
{
    int n;

    n = 0;
    while ((*all)->cmd->argv[n] != NULL)
        n++;
    if (n > 1 || check_digit((*all)->cmd->argv[0]) != 1)
    {
        ft_putstr_fd("bash: exit:", 2);
        if (check_digit((*all)->cmd->argv[0]) != 1)
        {
            ft_putstr_fd((*all)->cmd->argv[0], 2);
            ft_putstr_fd(": numeric argument required", 2);
            g_exit_status = 255;
        }
        else
        {
            ft_putstr_fd("too many arguments\n", 2);
            g_exit_status = 1;
        }
    }
    else if (n == 1)
	{
		ft_putstr_fd("exit\n", 1);
        g_exit_status = ft_atoi((*all)->cmd->argv[0]);
	}
    clear_all(*all);
	exit (g_exit_status);
}
