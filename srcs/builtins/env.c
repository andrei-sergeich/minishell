/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:59:23 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 18:59:24 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_executing(t_envl *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->value)
		{
			ft_putstr_fd(lst->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(lst->value, STDOUT_FILENO);
		}
		lst = lst->next;
	}
	return (0);
}
