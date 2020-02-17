/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:57:20 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/15 18:05:47 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static size_t	ft_deque_count(t_deque *deque)
{
	t_list	*it;
	size_t	n_nodes;

	it = ft_dequepeek(deque);
	n_nodes = 0;
	while (it && ++n_nodes)
		it = it->next;
	return (n_nodes);
}

static size_t	lastpad(t_deque *deque, int block_size, char *buffer, int cvt)
{
	t_list		*last;
	t_uintmax	len_bits;
	size_t		n;
	char		*it;

	last = ft_dequeeject(deque);
	len_bits = (ft_deque_count(deque) * block_size) + last->content_size * BYTE;
	ft_memcpy(buffer, last->content, last->content_size);
	it = buffer + last->content_size;
	ft_lstdelone(&last, &nodefree);
	*it = (char)(1 << (BYTE - 1));
	n = len_bits + BYTE;
	while ((block_size - block_size / BYTE) != n % block_size && (n += BYTE))
		*++it = 0;
	if (1024 == block_size)
	{
		*((t_uintmax *)++it) = len_bits;
		if (cvt)
			ft_endcvt(it, sizeof(t_uintmax), 1);
		return (n);
	}
	*((size_t *)++it) = len_bits;
	if (cvt)
		ft_endcvt(it, sizeof(size_t), 1);
	return (n);
}

void			padding(t_deque *deque, int block_size, int cvt)
{
	char		*it;
	size_t		n;
	char		buffer[1024];

	n = lastpad(deque, block_size, buffer, cvt) + block_size / BYTE;
	it = buffer;
	n -= ft_deque_count(deque) * block_size;
	while (n >= (size_t)block_size)
	{
		ft_dequesnoc(deque, it, block_size / BYTE);
		it += block_size / BYTE;
		n -= block_size;
	}
}
