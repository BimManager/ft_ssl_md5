/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdeque.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:01:33 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/13 14:07:31 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_deque		*ft_strdeque(const char *s, int block_size)
{
	t_deque	*deque;
	int		len_bits;

	deque = ft_dequenew();
	len_bits = ft_strlen(s) * BYTE;
	if (!len_bits)
	{
		ft_dequesnoc(deque, NULL, 0);
		return (deque);
	}
	while (len_bits >= block_size)
	{
		ft_dequesnoc(deque, s, block_size / BYTE);
		len_bits -= block_size;
		s += block_size / BYTE;
	}
	if (len_bits)
		ft_dequesnoc(deque, s, ft_strlen(s));
	return (deque);
}
