/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:46:57 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 15:07:22 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_arg(char *argum)
{
	int i;

	i = 0;
	while (argum[i] != '\0')
	{
		if (ft_isalpha(argum[i]) == 0 && ((ft_isdigit(argum[i]) != 0
		|| (ft_isdigit(argum[i]) == 0  && i == 0)) || (argum[i] != '_')))
				return (1);
		i++;
	}
	return (0);
}

void	add_arg(char *argum, t_env **my_env)
{
	int n;

	(*my_env)->name = ft_strcut(argum, '=');
	if ((n = ft_strfind(argum, '=')) != 0)
		(*my_env)->value = ft_strdup(&argum[n]);
	else
		(*my_env)->value = ft_strdup("");
	(*my_env)->standard = 2;
}

static void	write_var(t_env env_i)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env_i.name, 1);
	ft_putstr_fd("=", 1);
	ft_putstr_fd(env_i.value, 1);
	ft_putstr_fd("\n", 1);
}

int			ft_export(t_all **all)
{
	int i;
	t_env *sorted_env;

	i = 0;
	g_exit_status = 0;
	if((*all)->cmd->argv[0] == NULL)
	{
		if (!(sorted_env = copy_env((*all)->my_env)))
			return (ft_error("export", "out of memory", 12, NULL));
		sort_env(sorted_env);
		while (sorted_env[i].name != NULL)
			if (sorted_env[i].standard != 0)
			{
				write_var(sorted_env[i]);
				i++;
			}
		free_t_env(&sorted_env);
	}
	else
		while ((*all)->cmd->argv[i] != NULL)
		{
			if ((check_arg((*all)->cmd->argv[i])) == 1)
				ft_error("export", "not a valid identifier", 1,
				(*all)->cmd->argv[i]);
			else
				add_arg((*all)->cmd->argv[i], &(*all)->my_env);
			i++;
		}
	return (g_exit_status);
}
