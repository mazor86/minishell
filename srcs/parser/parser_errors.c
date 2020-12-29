/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:57:19 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 18:00:23 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** displays an error
**
** @param *all general structure
** @param *text error text
** @return 1
*/

static int	ret_err(t_all *all, char *text)
{
	all->res = 2;
	return (ft_error(NULL, text, 1));
}

/*
** Handles syntax errors
**
** @param *all general structure
** @param *lst command pointer
** @return 0 if no error was found, 1 error was found
*/

static int	parser_syntax_errors2(t_all *all, t_list *lst)
{
	if (!ft_strncmp(((t_cmd*)lst->content)->name, "", 1))
	{
		if (lst->next && !ft_strncmp(((t_cmd*)lst->next->content)->name, "", 1))
		{
			if (((t_cmd*)lst->content)->pipe &&
				((t_cmd*)lst->next->content)->pipe)
				return (ret_err(all, "syntax error \"||\""));
			else
				return (ret_err(all, "syntax error \";;\""));
		}
		if (((t_cmd*)lst->content)->pipe)
			return (ret_err(all, "syntax error \"|\""));
		else
			return (ret_err(all, "syntax error \";\""));
	}
	return (0);
}

/*
** Handles syntax errors
**
** @param *all general structure
** @return 0 if no error was found, 1 error was found
*/

int			parser_syntax_errors(t_all *all)
{
	t_list	*lst;

	lst = all->cmd;
	while (lst)
	{
		if (lst == all->cmd && !ft_strncmp(((t_cmd*)lst->content)->name,
			"", 1) && ((t_cmd*)lst->content)->pipe)
		{
			if (lst->next && !ft_strncmp(((t_cmd*)lst->next->content)->name,
				"", 1) && ((t_cmd*)lst->next->content)->pipe)
				return (ret_err(all, "syntax error \"||\""));
			else
				return (ret_err(all, "syntax error \"|\""));
		}
		if (parser_syntax_errors2(all, lst) == 1)
			return (1);
		lst = lst->next;
	}
	return (0);
}
