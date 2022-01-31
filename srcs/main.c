/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:55:43 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 18:58:01 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mini;

	(void)argc;
	(void)argv;
	g_ext_stat = 0;
	rl_outstream = stderr;
	mini = allocator(sizeof(t_shell));
	initializator(mini);
	mini->env_copy = copying_envp(envp);
	shlvl_up(mini);
	while (1)
	{
		sigs_interactive_shell();
		parser(mini, mini->env_copy);
		sigs_non_interactive_shell();
		if (mini->cmds)
			execute_cmds(mini, mini->cmds);
		liberator(mini);
	}
	liberator(mini);
	return (0);
}
