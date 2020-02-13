/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:46:54 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/12 12:33:54 by kkozlov          ###   ########.fr       */
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

static void		strfree(void *pv, size_t size)
{
	if (size)
		free(pv);
}

static size_t	ft_deque_count(t_deque *deque)
{
	t_list	*it;
	size_t	n_nodes;

	it = ft_dequepeek(deque);
	n_nodes = 0;
	while (it && ++n_nodes)
		it = it->next; 
	return (n_nodes);
}

void	padding(t_deque *deque, int block_size)
{
	char	*it;
	t_list	*last;
	size_t	lenbits;
	size_t	n;
	char	buffer[1024];

	ft_printf("deque_count: %llu\n", ft_deque_count(deque));	
	last = ft_dequeeject(deque);
	lenbits = (ft_deque_count(deque) * block_size) + last->content_size * BYTE;
	ft_printf("length_bits: %llu\n", lenbits);
	ft_memcpy(buffer, last->content, last->content_size);
//	ft_printf("before padding:\n%.*b\n", 2 * block_size, buffer);
	it = buffer + last->content_size;
	*it = (char)(1 << (BYTE - 1));
//	buffer[last->content_size] = (char)(1 << (BYTE - 1));
	ft_lstdelone(&last, &strfree);
//	ft_printf("after appending one:\n%.*b\n", 2 * block_size, buffer);
	n = lenbits + BYTE;
	while ((block_size - 64) != n % block_size)
	{
		n += BYTE;
		*++it = 0;
	}
	ft_printf("n: %llu\n", n);
//	*((size_t *)++it) = lenbits;
//	*(size_t *)(it + n / BYTE /8 ) = 0xffffffffffffffff;
//	*((size_t *)++it) = lenbits;
//	it = buffer;
//	*(size_t *)(it + n / BYTE) = lenbits;
//	*(size_t *)(it + n / BYTE) = 0xffffffff;
//	*((size_t *)++it) = 0xffffffff;
	*((size_t *)++it) = lenbits;
	n += 64;

//	*((size_t *)++it) = 0xffffffffffffffff;
	ft_printf("after padding:\n%.*b\n",block_size, buffer);
	ft_printf("n: %llu\n", n);
	ft_printf("n: %llu\n", n / BYTE);
	it = buffer;
	n -= ft_deque_count(deque) * block_size;
	while (n >= (size_t)block_size)
	{
		ft_dequesnoc(deque, it, block_size / BYTE);
		it += block_size / BYTE;
		n -= block_size;
	}
//	ft_dequesnoc(deque, it, n / BYTE);
//	ft_dequesnoc(deque, buffer, n / BYTE);
	//ft_printf("%.*b\n", 2 * block_size, buffer);
	ft_printf("n_blocks: %llu\n", ft_deque_count(deque));
}

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

t_uint32		*ft_md5(t_deque *deque)
{
	t_uint32	abcdfg[6];
	t_uint32	hashes[4];
	t_uint32	w[16];
	int			i;
	t_uint32	*digest;
	t_list		*it;

	padding(deque, 512);
	it = ft_dequepeek(deque);
	ft_memcpy(hashes, g_h03, sizeof(hashes));
	i = -1;
	while (it)
	{
		ft_printf("%.*b\n", it->content_size * BYTE, it->content);

		ft_memcpy(abcdfg, hashes, sizeof(hashes));
		ft_memcpy(w, it->content, sizeof(w));
		ft_printf("%.*s\n", 64, (char *)w);
		i = -1;
		while (++i < 64)
		{
			fgcalc(abcdfg, i, &abcdfg[4], &abcdfg[5]);
			abcdfg[4] += abcdfg[0] + g_k[i] + w[abcdfg[5]];
			abcdfg[0] = abcdfg[3];
			abcdfg[3] = abcdfg[2];
			abcdfg[2] = abcdfg[1];
			abcdfg[1] += (abcdfg[4] <<  g_s[i]) | (abcdfg[4] >> (32 - g_s[i]));
		}
		i = -1;
		while (++i < 4)
			hashes[i] += abcdfg[i];
		ft_printf("%u %u %u %u\n", hashes[0], hashes[1], hashes[2], hashes[3]);
		ft_printf("%x %x %x %x\n", hashes[0], hashes[1], hashes[2], hashes[3]);
		it = it->next;
	}
	digest = malloc(4 * sizeof(t_uint32));
	ft_memcpy(digest, hashes, 4 * sizeof(t_uint32));
	i = -1;
	while (++i < 4)
	{
		ft_swap(&digest[i], ((char *)&digest[i] + 3), sizeof(char));
		ft_swap((char *)&digest[i] + 1, (char *)&digest[i] + 2, sizeof(char));
	}
	return (digest);
}
