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
	printf("\nfrom main\n");
	print_cmds(mini->cmds);
//	print_redir(mini->cmds);
	print_args(mini->args);
//	print_env_copy(mini->env_copy);
	liberator(mini);
//	while (1);
	return (0);
}
