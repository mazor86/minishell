/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:42:38 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/27 21:44:55 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_error(char *name, char *text, int ret)
{
	if (name)
		ft_putstr_fd(name, 2);
	ft_putendl_fd(text, 2);
	return (ret);
}
