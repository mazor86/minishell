/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:13:05 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/25 10:25:46 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_env(t_all *all, t_cmd *cmd)
{
	t_list	*lst;

	(void)cmd;
	lst = all->env;
	while (lst)
	{
		if (((t_env*)lst->content)->par)
		{
			ft_putstr_fd(((t_env*)lst->content)->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(((t_env*)lst->content)->par, 1);
			ft_putstr_fd("\n", 1);
		}
		lst = lst->next;
	}
	all->res = 0;
	return (0);
}
