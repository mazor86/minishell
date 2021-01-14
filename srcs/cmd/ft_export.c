/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:46:57 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/11 11:42:49 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_arg(char *argum)
{
	int i;

	i = 0;
	while (argum[i] != '\0' && argum[i] != '=')
	{
		if (ft_isalpha(argum[i]) == 0)
		{
			if (argum[i] != '_' && ft_isdigit(argum[i]) == 0)
				return (1);
			if (ft_isdigit(argum[i]) == 0  && i == 0)
				return (1);
		}
		i++;
	}
	if (argum[i] == '=' && i == 0)
		return (1);
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

int			ft_export(t_all *all, t_cmd *cmd)
{
	int		i;
	t_env *begin;
	t_env *sorted_env;

	i = 0;
	all->exit_status = 0;
	if(ft_strncmp(cmd->argv[0],"", 1) == 0)
	{
		if (!(sorted_env = copy_env(all->my_env)))
			return (ft_error("export", "out of memory", 12, all));
		//sort_env(&sorted_env);
		begin = sorted_env;
		while (sorted_env != NULL)
			if (sorted_env->standard != 0)
			{
				write_var(*sorted_env);
				sorted_env = sorted_env->next;
			}
		free_t_env(&begin);
	}
	else
		while (cmd->argv[i] != NULL)
		{
			if ((check_arg(cmd->argv[i])) == 1)
				ft_error("export", "not a valid identifier", 1,
				all);
			else
				add_arg(cmd->argv[i], &all->my_env);
			i++;
		}
	return (all->exit_status);
}
