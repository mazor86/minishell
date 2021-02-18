/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:18:46 by mazor             #+#    #+#             */
/*   Updated: 2021/02/18 17:18:46 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*res;
	unsigned char	*res1;

	if (n == 0 || dest == src)
		return (dest);
	res = dest;
	res1 = (unsigned char *)src;
	while (n > 0)
	{
		res[n - 1] = res1[n - 1];
		n--;
	}
	return (dest);
}
