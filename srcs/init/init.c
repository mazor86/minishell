/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:38:32 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 17:32:40 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** creates a command structure
**
** @return command pointer, otherwise NULL
*/

t_list	*init_cmd(void)
{
	t_cmd	*cmd;
	t_list	*res;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->name = ft_strdup("");
	if (!(cmd->argv = ft_calloc(2, sizeof(char*))) ||
		!(cmd->argv[0] = ft_strdup("")))
		return (NULL);
	cmd->argv[1] = 0;
	cmd->pipe = 0;
	if (!(res = ft_lstnew(cmd)))
		free(cmd);
	return (res);
}

/*
** checks that the command is empty
**
** @param *lst pointer to command structure
** @return 1 if the command is empty, otherwise 0
*/

int		is_null_cmd(t_list *lst)
{
	if (!ft_strncmp(((t_cmd*)lst->content)->name, "", 1))
		return (1);
	return (0);
}
