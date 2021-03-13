/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:22:41 by mazor             #+#    #+#             */
/*   Updated: 2021/03/13 02:44:51 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*res1;

	i = 0;
	res = (unsigned char *)s1;
	res1 = (unsigned char *)s2;
	while ((res[i] || res1[i]) && n > i)
	{
		if (res[i] != res1[i])
			return (res[i] - res1[i]);
		i++;
	}
	return (0);
}
