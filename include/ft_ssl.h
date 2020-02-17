/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:07:20 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 11:15:11 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

# include "libft.h"

# define USAGE_MSG	"usage: ./ft_lss command [-pqr] [-s string] [files ...]"
# define ILLOPT_MSG	"ft_ssl %s: illegal option -- %s"

# define RD_BUFF_SIZE	1024

typedef __uint128_t	t_uintmax;

typedef struct	s_algorithm
{
	char		*name;
	t_uint32	block_size;
	t_uint32	word_size;
	t_uint32	digest_size;
	void		*(*func)(t_deque *);
}				t_algorithm;

typedef union	u_options
{
	size_t		bits;
}				t_options;

typedef enum	e_srctype
{
	ECHO_STDIN,
	STRING,
	FILE,
}				t_srctype;

typedef struct	s_env
{
	t_options	options;
	t_algorithm	*algo;
}				t_env;

void			ft_ssl(t_env *env);
t_deque			*ft_fdread(int fd, int bsize);
t_deque			*ft_strdeque(const char *s, int block_size);
int				ft_getopt(int argc, char *const argv[], const char *options);
t_env			*ft_argparse(int argc, char *const argv[]);

void			*ft_md5(t_deque *deque);
void			*ft_sha224(t_deque *deque);
void			*ft_sha256(t_deque *deque);
void			*ft_sha384(t_deque *deque);
void			*ft_sha512(t_deque *deque);

void			ft_stdoutdigest(t_env *env);
void			ft_strdigest(t_env *env, const char *str);
void			ft_filedigest(t_env *env, const char *filename);

void			padding(t_deque *deque, int block_size, int cvt);
void			ft_endcvt(void *pv, size_t width, size_t nel);
t_env			*ft_envnew(void);
void			ft_envdel(t_env **env);

void			nodefree(void *pv, size_t size);
t_algorithm		*getalgo(const char *name);
t_uint32		rotr32(t_uint32 x, int n);
t_uint64		rotr64(t_uint64 x, int n);

#endif
