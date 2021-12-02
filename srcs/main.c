#include "../include/minishell.h"

char	*copy_value(char *env_part)
{
	int		it;
	char	*value;

	it = 0;
	while (env_part[it] != '=' && env_part[it] != '\0')
		it++;
	if (env_part[it] == '\0')
		value = NULL;
	else
		value = ft_strdup(&env_part[it + 1]);
	return (value);
}

char	*copy_key(char *env_part)
{
	int		it;
	char	*key;

	it = 0;
	while (env_part[it] != '=' && env_part[it] != '\0')
		it++;
	key = ft_substr(env_part, 0, it);
	return (key);
}

t_envl	*envl_lstnew(char *env_str)
{
	t_envl	*element;

	element = (t_envl *)malloc(sizeof(t_envl));
	if (!element)
		return (NULL);
	element->key = copy_key(env_str);
	if (ft_strcmp(element->key, "OLDPWD") == 0)
		element->value = NULL;
	else
		element->value = copy_value(env_str);
	element->next = NULL;
	return (element);
}

void	envl_lstadd_back(t_envl	**list, t_envl *new)
{
	t_envl	*last;

	if (!list || !new)
		exit(EXIT_FAILURE); /* or return */
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

t_envl	*copying_envp(char **envp)
{
	t_envl	*envp_copy;
	int		it;

	it = 0;
	envp_copy = NULL;
	while (envp[it])
	{
		envl_lstadd_back(&envp_copy, envl_lstnew(envp[it]));
		it++;
	}
	return (envp_copy);
}

void	*give_me_memory(size_t size)
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

int main(int argc, char **argv, char **envp)
{
	t_shell *mini;

	(void)argc;
	(void)argv;
//	rl_outstream = stderr;
	g_status = 0;
	mini = give_me_memory(sizeof(t_shell));
	mini->env_copy = copying_envp(envp);
	while (1)
	{
		mini->input = readline(BEGIN(49, 32)"minishell$ "CLOSE);
		if (!mini->input)
			break;
		if (*mini->input)			/* If the line has any text in it, */
			add_history (mini->input);		/* save it on the history. */
		free(mini->input);
	}
//	exit(9);
	return (0);
}
