/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:38:00 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/25 16:52:51 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		arg_len(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i] != NULL)
		i++;
	return (i);
}

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
** @return exitstatus
*/

int		ft_exit(t_all *all, t_cmd *cmd)
{
	int	n;

	n = arg_len(cmd);
	if (n > 1 || check_digit(cmd->argv[0]) != 1)
	{
		if (check_digit(cmd->argv[0]) != 1)
			ft_error("exit", "Numeric argument required", 255, all);
		else
			ft_error("exit", strerror(1), 1, all);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		if (n == 1)
			all->exit_status = ft_atoi(cmd->argv[0]);
	}
	free_t_env(&all->my_env);
	clear_all(all);
	close(all->save_fd[0]);
	close(all->save_fd[1]);
	exit(all->exit_status);
}
