/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:46:54 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/15 15:25:58 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char		g_s[] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

static t_uint32	g_k[] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

static t_uint32 g_h03[] =
{
	0x67452301, 0xefcdab89,
	0x98badcfe, 0x10325476
};

static void	fgcalc(t_uint32 *abcd, int i, t_uint32 *f, t_uint32 *g)
{
	if (15 >= i)
	{
		*f = (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
		*g = i;
	}
	else if (31 >= i)
	{
		*f = (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
		*g = (5 * i + 1) % 16;
	}
	else if (47 >= i)
	{
		*f = abcd[1] ^ abcd[2] ^ abcd[3];
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = abcd[2] ^ (abcd[1] | ~abcd[3]);
		*g = (7 * i) % 16;
	}
}

static void	hashcalc(t_uint32 *a_g, t_uint32 *hashes, void *content)
{
	t_uint32	w[16];
	int			i;

	ft_memcpy(a_g, hashes, 4 * sizeof(t_uint32));
	ft_memcpy(w, content, sizeof(w));
	i = -1;
	while (++i < 64)
	{
		fgcalc(a_g, i, &a_g[4], &a_g[5]);
		a_g[4] += a_g[0] + g_k[i] + w[a_g[5]];
		a_g[0] = a_g[3];
		a_g[3] = a_g[2];
		a_g[2] = a_g[1];
		a_g[1] += (a_g[4] << g_s[i]) | (a_g[4] >> (32 - g_s[i]));
	}
	i = -1;
	while (++i < 4)
		hashes[i] += a_g[i];
}

void		*ft_md5(t_deque *deque)
{
	t_uint32	a_g[6];
	t_uint32	hashes[4];
	int			i;
	t_uint32	*digest;
	t_list		*it;

	padding(deque, 512, 0);
	it = ft_dequepeek(deque);
	ft_memcpy(hashes, g_h03, sizeof(hashes));
	i = -1;
	while (it)
	{
		hashcalc(a_g, hashes, it->content);
		it = it->next;
	}
	digest = malloc(4 * sizeof(t_uint32));
	ft_memcpy(digest, hashes, 4 * sizeof(t_uint32));
	ft_endcvt(digest, sizeof(t_uint32), 4);
	return (digest);
}
