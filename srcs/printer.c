#include "../include/minishell.h"

void	print_env_copy(t_shell *mini)
{
	while (mini->env_copy)
	{
		printf("%s\n", mini->env_copy->line);
		printf("%s=%s\n", mini->env_copy->key, mini->env_copy->value);
		mini->env_copy = mini->env_copy->next;
	}
}
