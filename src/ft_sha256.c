/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:35:03 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/13 12:23:36 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static t_uint32	g_hashes[] =
{
	0x6a09e667, 0xbb67ae85,
	0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c,
	0x1f83d9ab, 0x5be0cd19
};

static t_uint32	g_k[] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2

};

t_uint32	ch(t_uint32 x, t_uint32 y, t_uint32 z)
{
	return ((x & y) ^ ((~x) & z));
}

t_uint32	maj(t_uint32 x, t_uint32 y, t_uint32 z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

t_uint32	rotr32(t_uint32 x, int n)
{
	return ((x >> n) | (x << (32 - n)));
}

t_uint32	c_sigma0(t_uint32 x)
{
	return (rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22));
}

t_uint32	c_sigma1(t_uint32 x)
{
	return (rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25));
}

t_uint32	sigma0(t_uint32 x)
{
	return (rotr32(x, 7) ^ rotr32(x, 18) ^ (x >> 3));
}

t_uint32	sigma1(t_uint32 x)
{
	return (rotr32(x, 17) ^ rotr32(x, 19) ^ (x >> 10));
}

#define ROTRW(x, n, w) (((x) >> (n)) | ((x) << (w - (n))))

static unsigned char	test_block[] = 
{
	0,  1,  2,  3,  4,  5,  6,  7, 
	8,  9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39, 
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63
};


/*
** 1. Prepare the message schedule
*/

/*static void	mschprep(t_uint32 *w, t_list *it)
{
	int	i;

	ft_memcpy(w, it->content, it->content_size);
	i = 15;
	while (++i < 64)
		w[i] = ROTRW(
		}*/

t_uint32	*ft_sha256(t_deque *deque)
{
	t_list		*it;
	t_uint32	hashes[8];
	t_uint32	w[64];
	t_uint32	a_h[8];
	t_uint32	temps[2];
	int			i;
	t_uint32	*digest;


	int			j;
	t_uint32	s1;
	t_uint32	s0;
//	t_uint32	ch;
//	t_uint32	maj;
//	t_uint32	temp1;
//	t_uint32	temp2;

	padding(deque, 512);
	it = ft_dequepeek(deque);
	ft_memcpy(hashes, g_hashes, sizeof(hashes));
	ft_printf("%.*b\n", it->content_size * BYTE, w);
	while (it)
	{
//		ft_memcpy(w, it->content, it->content_size);
		//	ft_bzero(w, it->content_size);
		ft_printf("%.*b\n", it->content_size * BYTE, w);
		ft_memcpy(w, test_block, sizeof(w));
		ft_printf("%.*b\n", it->content_size * BYTE, w);
		i = 15;
		while (++i < 64)
		{
			w[i] = sigma1(w[i - 2]) + w[i - 7]
				+ sigma0(w[i - 15]) + w[i - 16];
			ft_printf("sigma1: %x sigma0: %x; %x; %x\n",
					  sigma1(w[i - 2]), sigma0(w[i - 15]), w[i - 7],
					  w[i - 16]);
			ft_printf("w: %x\n", w[i]);
//			((x >> n) | (x << (32 - n)));
			s0 = ROTRW(w[i - 15], 7, 32) ^ ROTRW(w[i - 15], 18, 32) ^ (w[i - 15] >> 3);
			s1 = ROTRW(w[i - 2], 17, 32) ^ ROTRW(w[i - 2], 19, 32) ^ (w[i - 2] >> 10);
			w[i] = w[i - 16] + s0 + w[i - 7] + s1;
			ft_printf("w: %x\n", w[i]);
		}
		ft_memcpy(a_h, hashes, sizeof(a_h));
		i = -1;
		while (++i < 64)
		{
//			ft_printf("w[%d]: %x\n", i + 1, w[i]);
			temps[0] = a_h[7] + c_sigma1(a_h[4]) 
				+ ch(a_h[4], a_h[5], a_h[6]) + g_k[i] + w[i];
			temps[1] = c_sigma0(a_h[0]) + maj(a_h[0], a_h[1], a_h[2]);
			a_h[7] = a_h[6];
			a_h[6] = a_h[5];
			a_h[5] = a_h[4];
			a_h[4] = a_h[3] + temps[0];
			a_h[3] = a_h[2];
			a_h[2] = a_h[1];
			a_h[1] = a_h[0];
			a_h[0] = temps[0] + temps[1];
			j = -1;
			while (++j < 8)
				ft_printf("a_h[%d]: %x\n", j, a_h[j]);
			ft_printf("\n");
			
		}
		i = -1;
		while (++i < 8)
			hashes[i] += a_h[i];
		it = it->next;
	}

	i = -1;
	while (++i < 8)
		ft_printf("%x\n", hashes[i]);

	digest = malloc(8 * sizeof(t_uint32));
	ft_memcpy(digest, hashes, 8 * sizeof(t_uint32));
	i = -1;
	while (++i < 7)
	{
		ft_swap(&digest[i], ((char *)&digest[i] + 3), sizeof(char));
		ft_swap((char *)&digest[i] + 1, (char *)&digest[i] + 2, sizeof(char));
	}
	return (digest);
}
