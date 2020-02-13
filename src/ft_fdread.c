/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:07:22 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/12 10:50:24 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_deque		*ft_fdread(int fd, int bsize)
{
	char		buffer[RD_BUFF_SIZE];
	int			n;
	t_deque		*deque;

	deque = ft_dequenew();
	while ((n = read(fd, buffer, bsize)) > 0)
		ft_dequesnoc(deque, buffer, n);
	if (ft_deque_isempty(deque))
		ft_dequesnoc(deque, NULL, 0);

	t_list	*it;
	it = ft_dequepeek(deque);
	ft_printf("read:\n");
	while (it)
	{
		ft_printf("size: %llu content: %.*s\n",
				  it->content_size, it->content_size, it->content);
		it = it->next;
	}
	return (deque);
}
