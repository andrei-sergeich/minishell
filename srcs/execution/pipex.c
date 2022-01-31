/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:06:04 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:06:05 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_creation_error(t_cmdl *cmds)
{
	ft_putstr_fd(BEGIN(49, 32)"[minishell ]$ "CLOSE, STDERR_FILENO);
	ft_putendl_fd("fork: Resource temporarily unavailable", STDERR_FILENO);
	g_ext_stat = 128;
	while (cmds->next)
	{
		if (!cmds->pipe_fd[0] || !cmds->pipe_fd[1])
			break ;
		close(cmds->pipe_fd[0]);
		close(cmds->pipe_fd[1]);
		cmds = cmds->next;
	}
	return (1);
}

int	pipe_creator(t_cmdl *cmds)
{
	t_cmdl	*begin;

	begin = cmds;
	while (cmds->next)
	{
		if (pipe(cmds->pipe_fd) < 0)
			return (pipe_creation_error(begin));
		cmds->out = cmds->pipe_fd[1];
		cmds->next->in = cmds->pipe_fd[0];
		cmds = cmds->next;
	}
	return (0);
}
