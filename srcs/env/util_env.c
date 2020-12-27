/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:49:01 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/25 18:28:43 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		clear_env(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		free(((t_env*)(*lst)->content)->name);
		if (((t_env*)(*lst)->content)->par)
			free(((t_env*)(*lst)->content)->par);
		tmp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(tmp, free);
	}
	*lst = NULL;
}

int			free_env(t_env **tmp, t_list **lst)
{
	if (*tmp)
	{
		free((*tmp)->name);
		if ((*tmp)->par)
			free((*tmp)->par);
		free(*tmp);
	}
	if (*lst)
		free(*lst);
	return (-1);
}

int			update_env(t_all *all, char *name, char *txt, char is_created)
{
	t_list	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env*)tmp->content)->name, name,
			ft_strlen(name) + 1))
		{
			if (((t_env*)tmp->content)->par)
				free(((t_env*)tmp->content)->par);
			if (!(((t_env*)tmp->content)->par = ft_strdup(txt)))
				return (-1);
			return (0);
		}
		tmp = tmp->next;
	}
	if (is_created == 1)
	{
		if (add_env(all, name, ft_strdup(txt)) == -1)
			return (-1);
		all->env = sort_env(all->env);
	}
	return (0);
}

static void	sort_env1(t_list *res, t_list *tmp)
{
	t_list	*current;

	current = res;
	while (current->next && ft_strncmp(((t_env*)tmp->content)->name,
	((t_env*)current->next->content)->name,
	ft_strlen(((t_env*)tmp->content)->name) + 1) >= 0)
		current = current->next;
	tmp->next = current->next;
	current->next = tmp;
}

t_list		*sort_env(t_list *lst)
{
	t_list	*res;
	t_list	*tmp;

	res = NULL;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (!res || ft_strncmp(((t_env*)tmp->content)->name,
		((t_env*)res->content)->name,
		ft_strlen(((t_env*)tmp->content)->name) + 1) < 0)
		{
			tmp->next = res;
			res = tmp;
		}
		else
			sort_env1(res, tmp);
	}
	return (res);
}
