/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:07:22 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 10:22:07 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_deque		*ft_fdread(int fd, int bsize)
{
	char		buffer[RD_BUFF_SIZE];
	int			n[2];
	t_deque		*deque;

	deque = ft_dequenew();
	while ((n[0] = read(fd, buffer, bsize)) > 0)
	{
		if (n[0] < bsize)
			if ((n[1] = read(fd, buffer + n[0], bsize - n[0])) > 0)
			{
				ft_dequesnoc(deque, buffer, n[0] + n[1]);
				continue ;
			}
		ft_dequesnoc(deque, buffer, n[0]);
	}
	if (ft_deque_isempty(deque))
		ft_dequesnoc(deque, NULL, 0);
	return (deque);
}
