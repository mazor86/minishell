/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2020/12/20 23:18:30 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 16:49:55 by jlyessa          ###   ########.fr       */
=======
/*   Created: 2020/11/08 19:43:41 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/31 02:50:16 by tisabel          ###   ########.fr       */
>>>>>>> tisabel
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
<<<<<<< HEAD
	char	*pwd;

	(void)cmd;
	if (!(pwd = getcwd(NULL, 0)))
		return (-1);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
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
	{
		while (ft_strncmp((*my_env)[i].name, "PWD", ft_strlen((*my_env)[i].name)) != 0)
			i++;
		write(1, (*my_env)[i].value, ft_strlen((*my_env)[i].value));
		write(1, "\n", 1);
	}
>>>>>>> tisabel
	return (0);
}
