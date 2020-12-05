/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:57:00 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/05 22:23:57 by tisabel          ###   ########.fr       */
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

int	serch_extern(t_data *data, char ***my_env)
{
	(void)data;
	(void)my_env;
	if (ft_strcmp(data->name, "cat") != 0 || ft_strcmp(data->name, "ls") != 0)
	{
        printf("%s is an extern function\n", data->name); //
        return (1);
    }
    return (0);
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
        if (serch_extern(data, my_env) == 1)
            flag = 1;
    if (flag == 0)
		wrong_command(data, my_env);
}