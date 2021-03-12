/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:19:24 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 17:21:18 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*res1;

	i = 0;
	res = dest;
	res1 = (unsigned char *)src;
	while (i < n)
	{
		res[i] = res1[i];
		if (res[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
