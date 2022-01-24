#include "../include/minishell.h"

void	builtin_executing(t_shell *mini, t_cmdl *cmds)
{
	(void)mini;

//	if (!ft_strcmp(cmds->command[0], "cd"))
//		g_ext_stat = cd_executing(mini, cmds->command);
//	else if (!ft_strcmp(cmds->command[0], "echo"))
//		g_ext_stat = echo_executing(cmds->command);
//	else if (!ft_strcmp(cmds->command[0], "env"))
//		g_ext_stat = env_executing(mini->env_copy);
//	else if (!ft_strcmp(cmds->command[0], "exit"))
//		g_ext_stat = exit_executing(mini, cmds->command);
//	else if (!ft_strcmp(cmds->command[0], "export"))
//		g_ext_stat = export_executing(mini, cmds->command);
	if (!ft_strcmp(cmds->command[0], "pwd"))
		pwd_executing();
//		g_ext_stat = pwd_executing();
//	else if (!ft_strcmp(cmds->command[0], "unset"))
//		g_ext_stat = unset_executing(mini, cmds->command);
}

int	builtin_checker(char *command)
{
	if (command == NULL)
		return (0);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	else
		return (0);
}
