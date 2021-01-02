/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:39:57 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/02 13:18:17 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Clears the entire t_cmd structure
**
** @param **lst Pointer to sheet of structure t_cmd
*/

void	clear_cmd(t_cmd **cmd_lst)
{
	t_list	*tmp;
	int		i;

	tmp = *cmd_lst;
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
	ft_lstclear(cmd_lst, free);
}

/*
** Clears the entire t_all structure
**
** @param *all general structure
*/

int		clear_all(t_all *all)
{
	clear_cmd(&all->cmd);
	clear_env(&all->my_env);
	free(all->line);
	return (-1);
}

/*
** Clears an array of strings
**
** @param **text Pointer to array of strings
*/

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
