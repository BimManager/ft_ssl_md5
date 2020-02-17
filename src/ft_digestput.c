/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digestput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:55:23 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 12:55:36 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	xdigestput(t_env *env, void *digest, char nl)
{
	size_t	i;

	i = -1;
	while (++i < env->algo->digest_size / env->algo->word_size)
	{
		if (1024 == env->algo->block_size)
			ft_printf("%.16llx", *((t_uint64 *)digest + i));
		else
			ft_printf("%.8x", *((t_uint32 *)digest + i));
	}
	if (nl)
		ft_printf("\n");
}

static void	digest_put(t_env *env, void *digest,
						const char *src, t_srctype type)
{
	char	buffer[64];

	ft_memcpy(buffer, env->algo->name, ft_strlen(env->algo->name) + 1);
	ft_strupcase(buffer);
	if ((ECHO_STDIN == type) || env->options.bits & (1 << ('q' - 'a')))
		return (xdigestput(env, digest, 1));
	if (env->options.bits & (1 << ('r' - 'a')))
	{
		xdigestput(env, digest, 0);
		if (STRING == type)
			ft_printf(" \"%s\"\n", src);
		else if (FILE == type)
			ft_printf(" %s\n", src);
		return ;
	}
	if (STRING == type)
		ft_printf("%s (\"%s\") = ", buffer, src);
	else if (FILE == type)
		ft_printf("%s (%s) = ", buffer, src);
	xdigestput(env, digest, 1);
}

void		ft_stdoutdigest(t_env *env)
{
	t_deque	*deque;
	t_list	*it;
	void	*digest;

	deque = ft_fdread(STDOUT, env->algo->block_size / BYTE);
	if ((env->options.bits & (1 << ('p' - 'a'))))
	{
		it = ft_dequepeek(deque);
		while (it)
		{
			ft_printf("%.*s", it->content_size, it->content);
			it = it->next;
		}
	}
	digest = env->algo->func(deque);
	digest_put(env, digest, NULL, ECHO_STDIN);
	ft_dequedel(&deque, &nodefree);
	free(digest);
}

void		ft_strdigest(t_env *env, const char *str)
{
	t_deque	*deque;
	void	*digest;

	deque = ft_strdeque(str, env->algo->block_size);
	digest = env->algo->func(deque);
	digest_put(env, digest, str, STRING);
	ft_dequedel(&deque, &nodefree);
	free(digest);
}

void		ft_filedigest(t_env *env, const char *filename)
{
	int			fd;
	struct stat	stat;
	t_deque		*deque;
	void		*digest;

	if (-1 == (fd = open(filename, O_RDONLY)))
	{
		ft_printf("%s: %s: %s\n", env->algo->name, filename, strerror(errno));
		return ;
	}
	lstat(filename, &stat);
	if (S_ISDIR(stat.st_mode))
	{
		ft_printf("%s: %s: %s\n", env->algo->name, filename, "Is a directory");
		return ;
	}
	deque = ft_fdread(fd, env->algo->block_size / BYTE);
	close(fd);
	digest = env->algo->func(deque);
	digest_put(env, digest, filename, FILE);
	ft_dequedel(&deque, &nodefree);
	free(digest);
}
