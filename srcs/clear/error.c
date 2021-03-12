/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:42:38 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 23:53:30 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** displays an error
**
** @param *name name command
** @param *text error text
** @param ret return
** @return ret
*/

int		ft_error(char *name, char *text, int ret, t_all *all)
{
	ft_putstr_fd("bash: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(text, 2);
	all->exit_status = ret;
	return (all->exit_status);
}
