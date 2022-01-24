#include "../include/minishell.h"

void	executing(t_shell *mini, t_cmdl *cmds)
{
//	char	*file;
//	int		err;

	if (builtin_checker(cmds->command[0]))
	{
		builtin_executing(mini, cmds);
//		if (cmds->fork)
//			exit (g_status);
		return ;
	}
	else
	{
//		file = done_path(mini, cmds->command[0]);
//		if (!file)
//			execve(cmds->command[0], cmds->command, ms_envplist_to_array(mini->env_copy));
//		else
//			execve(file, cmds->command, ms_envplist_to_array(mini->env_copy));
//		err = errno;
//		ms_no_such(cmds->command[0]);
//		free(file);
//		if (err == 13)
//			exit(126);
//		else
			exit(127);
	}
}

void	execute_cmds(t_shell *mini, t_cmdl *cmds)
{
//	t_cmdl	*begin;
//	int		cmds_qnt;
//
//	begin = cmds;
//	cmds_qnt = cmds_lstsize(cmds);
	if (!cmds->next && builtin_checker(cmds->command[0]) && !cmds->redir)
	{
		executing(mini, cmds);
		return ;
	}
//	if (pipe_creator(cmds))
//		return ;
//	while (len_cmd--)
//	{
////		maybe if (cmds->command[0])
//		cmds->pid = fork();
//		cmds->fork = 1;
//		if (cmds->pid < 0)
//			ms_error("bash: fork: Resource temporarily unavailable");
//		else if (cmds->pid == 0)
//			child_proc(mini, cmds, begin);
//		cmds = cmds->next;
//	}
//	wail_all(begin);
//	return (0);
}