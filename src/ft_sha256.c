/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:35:03 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 11:14:20 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static t_uint32	g_h224[] =
{
	0xc1059ed8, 0x367cd507,
	0x3070dd17, 0xf70e5939,
	0xffc00b31, 0x68581511,
	0x64f98fa7, 0xbefa4fa4
};

static t_uint32	g_h256[] =
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

/*
** 1. Prepare the message schedule
*/

static void		msprep(t_uint32 *w, t_list *it)
{
	int	i;

	ft_memcpy(w, it->content, it->content_size);
	ft_endcvt(w, sizeof(t_uint32), 64);
	i = 15;
	while (++i < 64)
	{
		w[i] = ((rotr32(w[i - 2], 17) ^ rotr32(w[i - 2], 19) ^ (w[i - 2] >> 10))
			+ (rotr32(w[i - 15], 7) ^ rotr32(w[i - 15], 18) ^ (w[i - 15] >> 3))
				+ w[i - 7] + w[i - 16]);
	}
}

/*
** 3. Step 3
*/

static void		precompute(t_uint32 *a_h, t_uint32 *w)
{
	int			i;
	t_uint32	t1;
	t_uint32	t2;

	i = -1;
	while (++i < 64)
	{
		t1 = (rotr32(a_h[4], 6) ^ rotr32(a_h[4], 11) ^ rotr32(a_h[4], 25))
			+ ((a_h[4] & a_h[5]) ^ (~a_h[4] & a_h[6]))
			+ a_h[7] + g_k[i] + w[i];
		t2 = (rotr32(a_h[0], 2) ^ rotr32(a_h[0], 13) ^ rotr32(a_h[0], 22))
			+ ((a_h[0] & a_h[1]) ^ (a_h[0] & a_h[2]) ^ (a_h[1] & a_h[2]));
		a_h[7] = a_h[6];
		a_h[6] = a_h[5];
		a_h[5] = a_h[4];
		a_h[4] = a_h[3] + t1;
		a_h[3] = a_h[2];
		a_h[2] = a_h[1];
		a_h[1] = a_h[0];
		a_h[0] = t1 + t2;
	}
}

static t_uint32	*getdigest(t_uint32 *hashes)
{
	t_uint32	*digest;

	digest = malloc(8 * sizeof(t_uint32));
	ft_memcpy(digest, hashes, 8 * sizeof(t_uint32));
	return (digest);
}

void			*ft_sha256(t_deque *deque)
{
	t_list		*it;
	t_uint32	hashes[8];
	t_uint32	w[64];
	t_uint32	a_h[8];
	int			i;

	padding(deque, 512, 1);
	it = ft_dequepeek(deque);
	ft_memcpy(hashes, g_h256, sizeof(hashes));
	while (it)
	{
		msprep(w, it);
		ft_memcpy(a_h, hashes, sizeof(a_h));
		precompute(a_h, w);
		i = -1;
		while (++i < 8)
			hashes[i] += a_h[i];
		it = it->next;
	}
	return (getdigest(hashes));
}

void			*ft_sha224(t_deque *deque)
{
	t_list		*it;
	t_uint32	hashes[8];
	t_uint32	w[64];
	t_uint32	a_h[8];
	int			i;

	padding(deque, 512, 1);
	it = ft_dequepeek(deque);
	ft_memcpy(hashes, g_h224, sizeof(hashes));
	while (it)
	{
		msprep(w, it);
		ft_memcpy(a_h, hashes, sizeof(a_h));
		precompute(a_h, w);
		i = -1;
		while (++i < 8)
			hashes[i] += a_h[i];
		it = it->next;
	}
	return (getdigest(hashes));
}
