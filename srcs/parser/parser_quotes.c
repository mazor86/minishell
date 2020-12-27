/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:33:48 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/20 13:32:27 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
