/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:15:33 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:15:34 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_dup2(t_cmdl *cmds)
{
	if (cmds->in != STDIN_FILENO)
	{
		if (dup2(cmds->in, STDIN_FILENO) < 0)
			return (1);
		close(cmds->in);
	}
	if (cmds->out != STDOUT_FILENO)
	{
		if (dup2(cmds->out, STDOUT_FILENO) < 0)
			return (1);
		close(cmds->out);
	}
	return (0);
}
