#include "../include/minishell.h"

void	print_env_copy(t_envl *env_copy)
{
	while (env_copy)
	{
		printf("%s\n", env_copy->line);
		printf("%s=%s\n", env_copy->key, env_copy->value);
		env_copy = env_copy->next;
	}
}

void	print_args(t_argl *args)
{
	while (args)
	{
//		printf("%s\n", mini->args->arg_as_is);
		printf("cleaned - %s \t %d\n", args->arg_cleaned, args->redirect);
		args = args->next;
	}
}
