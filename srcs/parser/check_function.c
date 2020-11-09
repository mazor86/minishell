/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:57:00 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 13:16:09 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_funcs_array(int (**function)(t_list **command, char **my_env))
{
	function[0] = ft_echo;
	function[1] = ft_cd;
	function[2] = ft_pwd;
	function[3] = ft_export;
	function[4] = ft_unset;
	function[5] = ft_env;
	function[6] = ft_exit;
}

void	serch_extern(command, my_env)
{
	
}

void	check_name(t_list **command, char **my_env)
{
	int			i;
	int			flag;
	void		(*f[7])(t_list **command, char **my_env);
	static char	*func[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	flag = 0;
	init_funcs_array(f);
	while (i < 7)
	{
		if (ft_strcmp(func[i], (*command)->content->name) == 0)
		{
			f[i](command, my_env);
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		serch_extern(command, my_env);
	else
		// write a func, that links to the shell commands.
		wrong_command(command, my_env);
}