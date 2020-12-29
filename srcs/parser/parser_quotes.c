/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:33:48 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 18:12:02 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** gets a string inside strong quotes
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @return 0 if good, otherwise -1
*/

int		get_strong_quotes(t_all *all, char **text)
{
	all->pos++;
	while (all->line[all->pos] && all->line[all->pos] != '\'')
	{
		if (join_char(text, all->line[all->pos]) == -1)
			return (-1);
		all->pos++;
	}
	if (all->line[all->pos] == '\'')
		all->pos++;
	return (0);
}

/*
** gets the string inside the loose quotes
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @return 0 if good, otherwise -1
*/

int		get_quotes(t_all *all, char **text)
{
	all->pos++;
	while (all->line[all->pos] && all->line[all->pos] != '\"')
	{
		if (all->line[all->pos] == '\\')
		{
			if (get_shielding(all, text) == -1)
				return (-1);
		}
		else if (all->line[all->pos] == '$')
		{
			if (get_variables(all, text) == -1)
				return (-1);
		}
		else
		{
			if (join_char(text, all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	if (all->line[all->pos] == '\"')
		all->pos++;
	return (0);
}
