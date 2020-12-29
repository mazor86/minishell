/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:38:00 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 16:37:41 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** executes the exit command
**
** @param *all general structure
** @param *cmd command structure
** @return 0
*/

int		ft_exit(t_all *all, t_cmd *cmd)
{
	(void)cmd;
	clear_all(all);
	exit(all->res);
	return (0);
}
