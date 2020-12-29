/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 23:18:30 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 16:49:55 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** executes the pwd command
**
** @param *all general structure
** @param *cmd command structure
** @return 0 if good, otherwise -1
*/

int		ft_pwd(t_all *all, t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	if (!(pwd = getcwd(NULL, 0)))
		return (-1);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	all->res = 0;
	return (0);
}
