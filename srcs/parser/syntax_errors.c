/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:45:43 by mazor             #+#    #+#             */
/*   Updated: 2021/02/18 00:14:17 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *syntax_err_text(char *line)
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

int     begin_syntax_error(char c)
{
    if (c == '|' || c == '&' || c == ';')
        return (1);
    return (0);
}

int    trim_quote(char **line)
{
    char    c;

    if (**line == '\'' || **line == '\"')
    {
        c = **line;
        (*line)++;
        while (**line)
        {
            if (**line == c)
            {
                (*line)++;
                return (0);
            }
            else
                (*line)++;
        }
    }
    return (1);
}

int     check_syntax(t_all *all)
{
    char    *line;
    int     quote;

    line = all->line;
    quote = 0;
    if (begin_syntax_error(*line))
        return (ret_err(all, syntax_err_text(line)));
    while (*line)
    {
        quote = trim_quote(&line);
        if (*line)
            line++;
    }
    if (quote)
        return (ret_err(all, "syntax error near unexpected token `newline\'"));

    return (0);
}