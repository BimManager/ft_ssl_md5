/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:43:39 by kkozlov           #+#    #+#             */
/*   Updated: 2018/10/30 12:47:25 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	char *pbeg;

	pbeg = str;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str = *str + ('a' - 'A');
		++str;
	}
	return (pbeg);
}
