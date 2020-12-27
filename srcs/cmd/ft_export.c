/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 10:35:39 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/25 15:55:02 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	show_all_env(t_all *all)
{
	t_list	*lst;

	lst = all->env;
	while (lst)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(((t_env*)lst->content)->name, 1);
		if (((t_env*)lst->content)->par)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_env*)lst->content)->par, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		lst = lst->next;
	}
}

static int	update_env_local(t_all *all, char *text)
{
	char	*name;
	char	*par;
	t_env	*tmp;

	name = get_name_env(text);
	par = get_param_env(text);
	if (!(tmp = get_env(all, name)))
	{
		if (add_env(all, name, par) == -1)
			return (-1);
	}
	else
	{
		if (tmp->par)
			free(tmp->par);
		tmp->par = par;
	}
	return (0);
}

static int	is_valid_argv(char *text)
{
	if ((text[0] >= 'a' && text[0] <= 'z') || (text[0] >= 'A' && text[0] <= 'Z')
		|| text[0] == '_')
		return (1);
	ft_putstr_fd("export: \"", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\" this is an invalid identifier", 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int			ft_export(t_all *all, t_cmd *cmd)
{
	int		i;

	i = -1;
	all->res = 0;
	if (!ft_strncmp(cmd->argv[0], "", 1))
		show_all_env(all);
	else
	{
		while (cmd->argv[++i])
		{
			if (is_valid_argv(cmd->argv[i]))
			{
				if (update_env_local(all, cmd->argv[i]) == -1)
					return (-1);
				all->env = sort_env(all->env);
			}
			else
				all->res = 1;
		}
	}
	return (0);
}
