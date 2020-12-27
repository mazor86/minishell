/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:29:09 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/25 11:41:18 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_env(t_all *all, char *s)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*parent;

	lst = all->env;
	parent = NULL;
	while (lst)
	{
		if (!ft_strncmp(((t_env*)lst->content)->name, s, ft_strlen(s) + 1))
		{
			tmp = lst;
			lst = lst->next;
			if (parent)
				parent->next = lst;
			free(((t_env*)tmp->content)->name);
			if (((t_env*)tmp->content)->par)
				free(((t_env*)tmp->content)->par);
			free(tmp);
		}
		else
		{
			parent = lst;
			lst = lst->next;
		}
	}
}

int			ft_unset(t_all *all, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->argv[++i])
		delete_env(all, cmd->argv[i]);
	all->res = 0;
	return (0);
}
