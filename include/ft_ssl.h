/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:07:20 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/13 09:30:51 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

# define USAGE_MSG	"usage: ./ft_lss command [command opts] [command args]"
# define INVCMD_MSG	"ft_ssl:Error: '%s' is an invalid command.\n\n" \
					"Standard commands\n\n" \
					"Message Digest commands\nmd5\nsha256\n\n" \
					"Cipher commands\n"
# define ILLOPT_MSG	"ft_ssl %s: illegal option -- %s"

# ifdef BUFF_SIZE
#  undef BUFF_SIZE
# endif
# define BUFF_SIZE	64
# define BLOCK_SIZE	512
# define RD_BUFF_SIZE	4096

typedef struct	s_algorithm
{
	char		*name;
	t_uint32	block_size;
	t_uint32	word_size;
	t_uint32	digest_size;
	t_uint32	*(*func)(t_deque *);
}				t_algorithm;

typedef union	s_options
{
	size_t		bits;
	struct
	{
		char	a : 1;
		char	b : 1;
		char	c : 1;
		char	d : 1;
		char	e : 1;
		char	f : 1;
		char	g : 1;
		char	h : 1;
		char	i : 1;
		char	j : 1;
		char	k : 1;
		char	l : 1;
		char	m : 1;
		char	n : 1;
		char	o : 1;
		char	p : 1;
		char	q : 1;
		char	r : 1;
		char	s : 1;
		char	t : 1;
		char	u : 1;
		char	v : 1;
		char	w : 1;
		char	x : 1;
		char	y : 1;
		char	z : 1;
	};
}				t_options;

typedef struct	s_env
{
	t_options	options;
	t_algorithm	*algo;
}				t_env;

t_deque		*ft_fdread(int fd, int bsize);
int			ft_getopt(int argc, char *const argv[], const char *options);
t_env		*ft_argparse(int argc, char *const argv[]);

t_uint32	*ft_md5(t_deque *deque);
t_uint32	*ft_sha256(t_deque *deque);
t_uint32	*ft_sha512(t_deque *deque);

void		padding(t_deque *deque, int block_size);
t_env		*ft_envnew(void);

#endif
