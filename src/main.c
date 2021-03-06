/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:11:14 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 10:32:31 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char **argv)
{
	t_env		*env;

	env = ft_argparse(argc, argv);
	ft_envdel(&env);
	return (EXIT_SUCCESS);
}
