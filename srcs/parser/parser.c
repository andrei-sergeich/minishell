/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:11:31 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:11:32 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_shell *mini, t_envl *env_copy)
{
	(void)env_copy;
	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
	if (!mini->input)
		exit(g_ext_stat);
	if (*mini->input)
		add_history (mini->input);
	if (validator(mini->input) == 0)
	{
		mini->args = arguments_processing(mini);
		mini->cmds = commands_processing(mini);
	}
	free(mini->input);
	mini->input = NULL;
}
