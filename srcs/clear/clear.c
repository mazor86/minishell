/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:39:57 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/26 13:52:14 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_cmd(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = *lst;
	while (tmp)
	{
		i = -1;
		free(((t_cmd*)tmp->content)->name);
		if (((t_cmd*)tmp->content)->argv)
		{
			while (((t_cmd*)tmp->content)->argv[++i])
				free(((t_cmd*)tmp->content)->argv[i]);
		}
		free(((t_cmd*)tmp->content)->argv);
		tmp = tmp->next;
	}
	ft_lstclear(lst, free);
}

int		clear_all(t_all *all)
{
	clear_cmd(&all->cmd);
	clear_env(&all->env);
	free(all->line);
	return (-1);
}

void	*free_split(char **text)
{
	int		i;

	i = -1;
	if (text)
	{
		while (text[++i])
			free(text[i]);
		free(text);
	}
	return (NULL);
}
