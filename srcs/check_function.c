/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:57:00 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/07 17:05:08 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_funcs_array(int (**function)(t_list **command))
{
	//function[0] = echo;
	//function[1] = cd;
	//function[2] = pwd;
	//function[3] = export;
	//function[4] = unset;
	//function[5] = env;
	//function[6] = exit;
}

void	ft_check_name(t_list **command)
{
	int			i;
	int			flag;
	void		(*f[7])(t_list **command);
	static char	*func[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	flag = 0;
	init_funcs_array(f);
	while (i < 7)
	{
		if (ft_strcmp(func[i], (*command)->content->name) == 0)
		{
			f[i](command);
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		ft_serch_extern(command);
	else
		// write a func, that links to the shell commands.
		ft_wrong_command(command);
}