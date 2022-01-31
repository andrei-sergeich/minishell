/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:08:05 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:08:06 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_cmd_and_filename(t_shell *mini)
{
	t_cmdl	*cmd;
	t_redir	*rdr;
	int		it;

	cmd = mini->cmds;
	rdr = (t_redir *) mini->cmds->redir;
	while (cmd)
	{
		if (cmd->command)
		{
			it = 0;
			while (cmd->command[it])
			{
				cmd->command[it] = postparser(cmd->command[it], mini->env_copy);
				it++;
			}
		}
		while (rdr)
		{
			rdr->name = postparser(rdr->name, mini->env_copy);
			rdr = rdr->next;
		}
		cmd = cmd->next;
	}
}

t_cmdl	*commands_processing(t_shell *mini)
{
	t_argl	*tmp;
	t_argl	*cmd_begin;

	if (mini->args == NULL)
		return (NULL);
	tmp = mini->args;
	cmd_begin = tmp;
	if ((ft_strcmp(tmp->arg_origin, "|")) == 0)
		tmp = tmp->next;
	while (tmp)
	{
		if ((ft_strcmp(tmp->arg_origin, "|")) == 0)
		{
			cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
			cmd_begin = tmp->next;
		}
		tmp = tmp->next;
	}
	cmds_lstadd_back(&mini->cmds, cmds_lstnew(cmd_begin));
	clean_cmd_and_filename(mini);
	return (mini->cmds);
}
