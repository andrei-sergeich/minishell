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

void	print_args(t_shell *mini)
{
	while (mini->args)
	{
//		printf("%s\n", mini->args->arg_as_is);
		printf("as is - %s\t\tcleaned - %s\n", mini->args->arg_as_is, mini->args->arg_cleaned);
		mini->args = mini->args->next;
	}
}
