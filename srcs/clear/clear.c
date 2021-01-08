/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:39:57 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 17:32:41 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Clears the entire array of t_env structures
**
** @param **my_env
*/

void	free_t_env(t_env **my_env)
{
	int i;

	i = 0;
	while (my_env[i]->name != NULL)
	{
		free(my_env[i]->name);
		my_env[i]->name = NULL;
		free(my_env[i]->value);
		my_env[i]->value = NULL;
		my_env[i]->standard = 0;
		i++;
	}
	*my_env = NULL;
}

/*
** Clears the entire t_cmd structure
**
** @param **lst Pointer to sheet of structure t_cmd
*/

void	clear_cmd(t_cmd **cmd_lst)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd_lst;
	while (tmp)
	{
		i = -1;
		free(tmp->name);
		if (tmp->argv)
		{
			while (tmp->argv[++i])
				free(tmp->argv[i]);
		}
		free(tmp->argv);
		tmp = tmp->next;
	}
	*cmd_lst = NULL;
}

/*
** Clears the entire t_all structure
**
** @param *all general structure
*/

int		clear_all(t_all *all)
{
	clear_cmd(&all->cmd);
	free_t_env(&all->my_env);
	free(all->line);
	return (-1);
}

/*
** Clears an array of strings
**
** @param **text Pointer to array of strings
*/

void	*free_array(char **text)
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
