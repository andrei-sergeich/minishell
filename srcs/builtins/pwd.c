/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:00:24 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:00:30 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_executing(void)
{
	char	*pwd;

	pwd = ft_calloc(1024, sizeof(char));
	if (getcwd(pwd, 1024))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		return (0);
	}
	else
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(pwd);
		return (1);
	}
}
