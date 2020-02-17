/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 11:12:39 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 11:19:38 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const char	*g_invcmd_msg =
"ft_ssl:Error: '%s' is an invalid command.\n\n"
"Standard commands\n\n"
"Message Digest commands\n"
"md5\nsha224\nsha256\nsha384\nsha512\n\n"
"Cipher commands\n";

t_algorithm	g_algos[] =
{
	{ "md5", 512, 32, 128, &ft_md5 },
	{ "sha224", 512, 32, 224, &ft_sha224 },
	{ "sha256", 512, 32, 256, &ft_sha256 },
	{ "sha384", 1024, 64, 384, &ft_sha384 },
	{ "sha512", 1024, 64, 512, &ft_sha512 }
};

void		nodefree(void *pv, size_t size)
{
	if (size)
		free(pv);
}

t_algorithm	*getalgo(const char *name)
{
	int	i;

	i = sizeof(g_algos) / sizeof(g_algos[0]);
	while (i--)
		if (0 == ft_strcmp(name, g_algos[i].name))
			return (&g_algos[i]);
	return (NULL);
}

t_uint32	rotr32(t_uint32 x, int n)
{
	return ((x >> n) | (x << (32 - n)));
}

t_uint64	rotr64(t_uint64 x, int n)
{
	return ((x >> n) | (x << (64 - n)));
}
