/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:48:18 by mazor             #+#    #+#             */
/*   Updated: 2021/02/18 18:46:53 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*syntax_err_text(char *line)
{
	if (*(line + 1) && *line == *(line + 1))
	{
		if (*line == '|')
			return ("syntax error \"||\"");
		if (*line == ';')
			return ("syntax error \";;\"");
		if (*line == '&')
			return ("syntax error \"&&\"");
	}
	if (*line == '|')
		return ("syntax error \"|\"");
	if (*line == ';')
		return ("syntax error \";\"");
	if (*line == '&')
		return ("syntax error \"&\"");
	return ("syntax error");
}

char	*syntax_err_flag_to_text(int flag)
{
	if (flag == 4)
		return ("syntax error near unexpected token `newline'");
	if (flag == 3)
		return ("syntax error near unexpected token `;'");
	if (flag == 2)
		return ("syntax error near unexpected token `|'");
	if (flag == 1)
		return ("syntax error near unexpected token `;;'");
	return ("syntax error");
}

int		trim_space_in_line(char **line)
{
	int space;

	space = (**line == ' ');
	while (**line == ' ')
		((*line)++);
	return (space);
}