/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:49:48 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/05 23:37:02 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(t_data *data, t_var **my_env)
{
    int n;

    n = 0;
    while (data->argum[n] != NULL)
        n++;
    ft_putstr_fd("exit\n", 1);
    if (n > 1 || check_digit(data->argum[0]) != 1)
    {
        ft_putstr_fd("bash: exit:", 2);
        if (check_digit(data->argum[0]) != 1)
        {
            ft_putstr_fd(data->argum[0], 2);
            ft_putstr_fd(": numeric argument required", 2);
            exit (255);
        }
        else
        {
            ft_putstr_fd("too many arguments\n", 2);
            return (g_exit_status = 1);
        }
    }
    else if (n == 1)
        g_exit_status = ft_atoi(data->argum[0]);
    free_array(my_env);
    free_struct(data);
	exit (g_exit_status);
}
