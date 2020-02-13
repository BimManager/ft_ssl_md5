/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:08:19 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/08 13:57:04 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	ft_getopt(int argc, char *const argv[], const char *options)
{
	static int	i;
	const char	*it;
	const char	*opt;

	while (++i < argc)
	{
		if ('-' != *(it = argv[i]))
			return (-1);
		++it;
		if ((opt = ft_strchr(options, *it)))
		{
			if (':' != *(opt + 1))
				return (*opt);
			else if (i == argc - 1)
				return ('?');
			++i;
			return (*opt);
		}
		else
			return ('?');
	}
	return (-1);
}
