/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:45:35 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/01 17:05:15 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(t_data *data, t_var **my_env)
{
	int i;
	int n;
	char *path;

	i = 0;
	path = data->argum[0] == NULL ? get_home(my_env) : data->argum[0];
	if (chdir(path) < 0)
	{
		write (1, "error", 5);
		exit (2); // set error path not found or other
	}
	change_var("OLD_PWD", get_var(my_env, "PWD"));
	change_var("PWD", getcwd(NULL, _PC_PATH_MAX));
	return (0);
}
