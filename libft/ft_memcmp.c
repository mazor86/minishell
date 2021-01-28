/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:     mazor <mazor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:10:48 by mazor             #+#    #+#             */
/*   Updated: 2020/12/03 21:26:17 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*res1;

	i = 0;
	res = (unsigned char *)s1;
	res1 = (unsigned char *)s2;
	while (n > i)
	{
		if (res[i] != res1[i])
			return (res[i] - res1[i]);
		i++;
	}
	return (0);
}
