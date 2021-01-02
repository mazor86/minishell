/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2020/12/25 10:13:05 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 16:37:09 by jlyessa          ###   ########.fr       */
=======
/*   Created: 2020/11/08 19:48:51 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/31 02:52:14 by tisabel          ###   ########.fr       */
>>>>>>> tisabel
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** executes the env command
**
** @param *all general structure
** @param *cmd command structure
** @return 0
*/

int		ft_env(t_all *all, t_cmd *cmd)
{
<<<<<<< HEAD
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
=======
	int i;

	i = 0;
	if(data->argum[0] != 0)
		{
			write(1, "Error. Wrong number of arguments.", 34);
			g_exit_status = 2;
			exit(g_exit_status);
		}
	else
		while ((*my_env)[i].name != NULL)
		{
			if ((*my_env)[i].standard == 1)
			{
				write(1, (*my_env)[i].name, ft_strlen((*my_env)[i].name));
				write(1, "=", 1);
				write(1, (*my_env)[i].value, ft_strlen((*my_env)[i].value));
				write(1, "\n", 1);
			}
		i++;
		}
>>>>>>> tisabel
	return (0);
}
