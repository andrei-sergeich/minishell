#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mini;
//	int	g_ext_stat;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
//	g_ext_stat = 0;
	mini = allocator(sizeof(t_shell));
	mini->env_copy = copying_envp(envp);
	shlvl_up(mini);
//		while (mini->env_copy)
//	{
//		printf("%s\n", mini->env_copy->line);
//		printf("%s=%s\n", mini->env_copy->key, mini->env_copy->value);
//		mini->env_copy = mini->env_copy->next;
//	}
//	while (1)
//	{
		parsing(mini, mini->env_copy);
//	}
	liberator(mini);
//	while (1);
//	exit(9);
	return (0);
}
