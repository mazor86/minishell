/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:39:07 by jlyessa           #+#    #+#             */
/*   Updated: 2020/11/08 19:42:59 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_echo(t_data *data)
{
	if (ft_strncmp(data->flag, "-n", 3))
		ft_putstr_fd(data->argum, 1);
	else
		ft_putendl_fd(data->argum, 1);
	return (1);
}
