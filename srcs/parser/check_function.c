/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:57:00 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/09 22:12:21 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_funcs_array(int (**function)(t_data *data, char ***my_env))
{
	function[0] = ft_echo;
	function[1] = ft_cd;
	function[2] = ft_pwd;
	function[3] = ft_export;
	function[4] = ft_unset;
	function[5] = ft_env;
	function[6] = ft_exit;
}

void	serch_extern(t_data *data, char ***my_env)
{
	(void)data;
	(void)my_env;
}

void	check_name(t_data *data, char ***my_env)
{
	int			i;
	int			flag;
	int			(*f[7])(t_data *data, char ***my_env);
	static char	*func[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	flag = 0;
	init_funcs_array(f);
	while (i < 7)
	{
		if (ft_strcmp(func[i], data->name) == 0)
		{
			f[i](data, my_env);
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		serch_extern(data, my_env);
	else
		// write a func, that links to the shell commands.
		wrong_command(data, my_env);
}