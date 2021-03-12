/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:39:57 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 17:21:18 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Clears the entire array of t_env structures
**
** @param **my_env
*/

void	del_one_env(t_env *my_env)
{
	if (my_env->name)
	{
		free(my_env->name);
		my_env->name = NULL;
	}
	if (my_env->value)
	{
		free(my_env->value);
		my_env->value = NULL;
	}
	my_env->standard = 0;
}

void	free_t_env(t_env **my_env)
{
	t_env	*temp;
	t_env  *save;

	if (my_env)
	{
		temp = *my_env;
		while (temp)
		{
			save = temp->next;
			del_one_env(temp);
			free(temp);
			temp = save;
		}
	}
}

/*
** Clears the entire t_cmd structure
**
** @param **lst Pointer to sheet of structure t_cmd
*/

void	clear_cmd(t_cmd **cmd_lst)
{
	t_cmd	*tmp;
	t_cmd	*save;
	int		i;

	if (cmd_lst)
	{
		tmp = *cmd_lst;
		while (tmp) {
			save = tmp->next;
			i = -1;
			if (tmp->name) {
				free(tmp->name);
				tmp->name = NULL;
			}
			if (tmp->argv) {
				while (tmp->argv[++i])
					free(tmp->argv[i]);
			}
			free(tmp->argv);
			clear_redir(tmp->redir);
			free(tmp);
			tmp = save;
		}
        *cmd_lst = NULL;
	}
}

/*
** Clears the entire t_all structure
**
** @param *all general structure
*/

int		clear_all(t_all *all)
{
	clear_cmd(&all->cmd);
	free(all->line);
	return (all->exit_status);
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
	if (text && *text)
	{
		while (text[++i])
		{
			free(text[i]);
			text[i] = NULL;
		}
		free(text);
		text = NULL;
	}
	return (NULL);
}
