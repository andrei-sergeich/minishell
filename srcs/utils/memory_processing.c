#include "../include/minishell.h"

void	*allocator(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Could not malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	initializator(t_shell *mini)
{
	mini->input = NULL;
	mini->env_copy = NULL;
	mini->cmds = NULL;
	mini->args = NULL;
}

void	liberator(t_shell *mini)
{
//	envl_destroy(&mini->env_copy);
	args_destroy(&mini->args);
//	redir_destroy(&mini->cmds->redir);
	cmds_destroy(&mini->cmds);
//	free(mini);
}

void	array_liberator(char **array)
{
	int	it;

	it = 0;
	while (array[it])
	{
		free(array[it]);
		array[it] = NULL;
		it++;
	}
	free(array);
	array = NULL;
}
