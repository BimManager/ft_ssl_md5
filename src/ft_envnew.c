/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkozlov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 10:42:03 by kkozlov           #+#    #+#             */
/*   Updated: 2020/02/16 10:31:57 by kkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_env	*ft_envnew(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	ft_bzero(&env->options, sizeof(size_t));
	return (env);
}

void	ft_envdel(t_env **env)
{
	free(*env);
	*env = NULL;
}
