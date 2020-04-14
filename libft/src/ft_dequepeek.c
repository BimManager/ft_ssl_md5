/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequepeek.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 12:39:30 by kkozlov           #+#    #+#             */
/*   Updated: 2019/12/29 12:43:06 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_dequepeek(const t_deque *deque)
{
	return (deque->head);
}