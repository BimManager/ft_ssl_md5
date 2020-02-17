/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:01:24 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 11:15:51 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern const char	*g_invcmd_msg;

void				xparse_gt2(int argc, char *const argv[], t_env *env)
{
	char	*options;
	int		opt;
	int		i;

	i = 1;
	options = "pqrs:";
	while (-1 != (opt = ft_getopt(argc - 1, argv + 1, options)) && ++i)
	{
		if ('?' == opt || (2 < ft_strlen(argv[i])))
			ft_die(USAGE_MSG, 3);
		env->options.bits |= 1 << (opt - 'a');
		if ('p' == opt)
			ft_stdoutdigest(env);
		if ('s' == opt)
		{
			++i;
			ft_strdigest(env, argv[i]);
		}
	}
	if (i < argc - 1)
		while (++i < argc)
			ft_filedigest(env, argv[i]);
	else if (!(env->options.bits & (1 << ('s' - 'a')))
			&& !(env->options.bits & (1 << ('p' - 'a'))))
		ft_stdoutdigest(env);
}

t_env				*ft_argparse(int argc, char *const argv[])
{
	t_env	*env;

	env = ft_envnew();
	if (1 == argc)
		ft_die(USAGE_MSG, 1);
	else if (!(env->algo = getalgo(argv[1])))
	{
		ft_printf(g_invcmd_msg, argv[1]);
		exit(2);
	}
	else if (2 == argc)
		ft_stdoutdigest(env);
	else
		xparse_gt2(argc, argv, env);
	return (env);
}
