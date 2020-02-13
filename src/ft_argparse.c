/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:01:24 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/10 18:10:38 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_algorithm	g_algos[] =
{
	{ "md5", 512, 32, 128, &ft_md5 },
	{ "sha256", 512, 32, 256, &ft_sha256 }
};

static t_algorithm	*getalgo(const char *name)
{
	int	i;

	i = sizeof(g_algos) / sizeof(g_algos[0]);
	while (i--)
		if (0 == ft_strcmp(name, g_algos[i].name))
			return (&g_algos[i]);
	return (NULL);
}

t_env	*ft_argparse(int argc, char *const argv[])
{
	t_env	*env;
	char	*options;
	int		opt;

	env = ft_envnew();
	if (1 == argc)
		ft_die(USAGE_MSG, 1);
	else if (!(env->algo = getalgo(argv[1])))
	{
		ft_printf(INVCMD_MSG, argv[1]);
		exit(2);
	}
	options = "pqrs:";
	while (-1 != (opt = ft_getopt(argc - 1, argv + 1, options)))
	{
		if ('?' == opt)
			ft_die("invalid option\n", 3);
		env->options.bits |= 1 << (opt - 'a');
	}
	ft_printf("%.26b\n", &env->options.bits);
//	else
		//ft_printf(INVCMD_MSG, argv[1]);
	return (env);
}
