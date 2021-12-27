#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mini;
//	int	g_ext_stat;

	(void)argc;
	(void)argv;
//	g_ext_stat = 0;
	rl_outstream = stderr;
	mini = allocator(sizeof(t_shell));
	mini->env_copy = copying_envp(envp);
	shlvl_up(mini);
//	print_env_copy(mini);
//	while (1)
//	{
		parser(mini, mini->env_copy);
//	}
	liberator(mini);
//	while (1);
//	exit(9);
	return (0);
}
