#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell *mini;
	int	g_ext_stat;

	(void)argc;
	(void)argv;
//	rl_outstream = stderr;
	g_ext_stat = 0;
	mini = allocator(sizeof(t_shell));
	mini->env_copy = copying_envp(envp);
	shlvl_up(mini);
	while (1)
	{
		mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
		if (!mini->input)
			break;
		if (*mini->input)			/* If the line has any text in it, */
			add_history (mini->input);		/* save it on the history. */
		free(mini->input);
	}
	liberator(mini);
//	exit(9);
	return (0);
}
