/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:38:32 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 00:06:42 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** creates a command structure
**
** @return command pointer, otherwise NULL
*/

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->name = ft_strdup("");
	if (!(cmd->argv = ft_calloc(2, sizeof(char*))) ||
		!(cmd->argv[0] = ft_strdup("")))
		return (NULL);
	cmd->argv[1] = 0;
	cmd->pipe = 0;
	cmd->next = NULL;
	return (cmd);
}

/*
** checks that the command is empty
**
** @param *lst pointer to command structure
** @return 1 if the command is empty, otherwise 0
*/

int		is_null_cmd(t_cmd *lst)
{
	if (!ft_strncmp(lst->name, "", 1))
		return (1);
	return (0);
}
