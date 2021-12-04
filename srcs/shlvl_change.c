#include "../include/minishell.h"

void	shlvl_down(t_shell *mini)
{
	char	*cur_lvl;
	char	*up_lvl;

	cur_lvl = find_in_env(mini->env_copy, "SHLVL");
//	printf("cur is %s\n", cur_lvl);
	up_lvl = ft_itoa(ft_atoi(cur_lvl) - 1);
	change_value_in_env_copy(mini->env_copy, "SHLVL", up_lvl);
//	printf("up is %s\n", up_lvl);
//	while (mini->env_copy)
//	{
//		printf("%s\n", mini->env_copy->line);
//		printf("%s=%s\n", mini->env_copy->key, mini->env_copy->value);
//		mini->env_copy = mini->env_copy->next;
//	}

	free(up_lvl);
}

void	shlvl_up(t_shell *mini)
{
	char	*cur_lvl;
	char	*up_lvl;

	cur_lvl = find_in_env(mini->env_copy, "SHLVL");
//	printf("cur is %s\n", cur_lvl);
	up_lvl = ft_itoa(ft_atoi(cur_lvl) + 1);
	change_value_in_env_copy(mini->env_copy, "SHLVL", up_lvl);
//	printf("up is %s\n", up_lvl);
//	while (mini->env_copy)
//	{
//		printf("%s\n", mini->env_copy->line);
//		printf("%s=%s\n", mini->env_copy->key, mini->env_copy->value);
//		mini->env_copy = mini->env_copy->next;
//	}

	free(up_lvl);
}
