/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:12:22 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:18:00 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(char *argument)
{
	if ((ft_strcmp(argument, ">") == 0)
		|| (ft_strcmp(argument, ">>") == 0)
		|| (ft_strcmp(argument, "<") == 0)
		|| (ft_strcmp(argument, "<<") == 0))
		return (1);
	return (0);
}

void	set_redirect(t_argl *args)
{
	while (args)
	{
		if (is_redirect(args->arg_origin) == 1)
		{
			args->redirect = 1;
			args->next->redirect = 2;
			args = args->next->next;
		}
		else if (args)
			args = args->next;
	}
}
