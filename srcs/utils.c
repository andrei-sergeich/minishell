#include "../include/minishell.h"

char	*find_in_env(t_envl *env_copy, char *key)
{
	if (!env_copy || !key)
		return (NULL);
	while (env_copy)
	{
		if (!ft_strcmp(env_copy->key, key))
			return (env_copy->value);
		env_copy = env_copy->next;
	}
	return (NULL);
}

void	change_value_in_env_copy(t_envl *env_copy, char *key, char *value)
{
	if (!env_copy || !key || !value)
		return ;
	while (env_copy)
	{
		if (!ft_strcmp(env_copy->key, key))
		{
			if (env_copy->line)
				free(env_copy->line);
			env_copy->line = ft_strjoin_con(key, "=", value);
			if (env_copy->value)
				free(env_copy->value);
			env_copy->value = ft_strdup(value);
			return ;
		}
		env_copy = env_copy->next;
	}
}

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

void	liberator(t_shell *mini)
{
	while (mini->env_copy)
	{
		free(mini->env_copy->line);
		free(mini->env_copy->key);
		free(mini->env_copy->value);
		mini->env_copy = mini->env_copy->next;
	}
	free(mini);
}