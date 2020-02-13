/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:11:14 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/12 12:36:01 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char **argv)
{
	t_env		*env;
	t_deque		*deque;
	t_uint32	*digest;
	size_t		i;

	env = ft_argparse(argc, argv);
	deque = ft_fdread(STDOUT, env->algo->block_size / BYTE);
	digest = env->algo->func(deque);
	i = -1;
	while (++i < env->algo->digest_size / (sizeof(t_uint32) * BYTE))
		ft_printf("%.8x", digest[i]);
	return (EXIT_SUCCESS);
}
