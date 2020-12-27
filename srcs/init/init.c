/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:38:32 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/22 10:27:37 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	cmd->pipe_start = 0;
	cmd->pipe_end = 0;
	if (!(res = ft_lstnew(cmd)))
		free(cmd);
	return (res);
}
