#include "../include/minishell.h"

void	print_env_copy(t_envl *env_copy)
{
	if (env_copy == NULL)
		return ;
	while (env_copy)
	{
		printf("%s\n", env_copy->line);
		printf("%s=%s\n", env_copy->key, env_copy->value);
		env_copy = env_copy->next;
	}
}

void	print_args(t_argl *args)
{
	if (args == NULL)
		return ;
	while (args)
	{
//		printf("%s\n", mini->args->arg_as_is);
		printf("cleaned - |%s| \t %d\n", args->arg_cleaned, args->redirect);
		args = args->next;
	}
}

void	print_cmds(t_cmdl *cmds)
{
	int	it;

	if (cmds == NULL)
		return ;
	while (cmds)
	{
		it = 0;
		while (cmds->command[it])
		{
			printf("command[%d] - |%s|\t in - |%d|\t out - |%d|\n", it, cmds->command[it], cmds->in, cmds->out);
			it++;
		}
		cmds = cmds->next;
	}
}

void	print_redir(t_redir *rdr)
{
	if (rdr == NULL)
		return ;
	while (rdr)
	{
//		printf("%s\n", mini->args->arg_as_is);
		printf("type - |%s| \t name - |%s|\n", rdr->type, rdr->name);
		rdr = rdr->next;
	}
}
