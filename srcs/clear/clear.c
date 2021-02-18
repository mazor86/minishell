/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:39:57 by mazor             #+#    #+#             */
/*   Updated: 2021/01/08 17:32:41 by tisabel          ###   ########.fr       */
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
	free(my_env->name);
	my_env->name = NULL;
	free(my_env->value);
	my_env->value = NULL;
	my_env->next = NULL;
	my_env->standard = 0;
}

void	free_t_env(t_env **my_env)
{
	t_env	*temp;

	if (my_env)
		while (*my_env)
		{
			temp = (*my_env)->next;
			del_one_env(*my_env);
			free(*my_env);
			*my_env = temp;
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
	int		i;

	tmp = *cmd_lst;
	while (tmp)
	{
		i = -1;
		if (tmp->name)
		    free(tmp->name);
		if (tmp->argv)
		{
			while (tmp->argv[++i])
				free(tmp->argv[i]);
		}
		free(tmp->argv);
		clear_redir(tmp->redir);
		tmp = tmp->next;
	}
	free(*cmd_lst);
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
