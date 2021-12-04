#include "../include/minishell.h"

char	*quote(char *str, int *it)
{
	int		begin;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	begin = *it;
	while (str[*it])
	{
		if (str[*it] == '\'')
			break;
		it++;
	}
	tmp = ft_substr(str, 0, begin);
	tmp2 = ft_substr(str, begin + 1, *it - begin - 1);
//	printf("tmp2 = %s\n", tmp2);
	tmp3 = ft_strdup(str + *it + 1);
//	printf("tmp3 = %s\n", tmp3);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
//	printf("tmp = %s\n", tmp);
	free(str);
	return (tmp);
}

void	preparser(char *str)
{
	int	it;

	it = 0;
	while (str[it])
	{
		if (str[it] == '\'')
			str = quote(str, &it);
		it++;
	}
	printf("tmp = %s\n", str);

}

void	parsing(t_shell *mini, t_envl *env_copy)
{
	(void)env_copy;
	mini->input = NULL;
	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
	if (!mini->input)
		exit(0);
	if (*mini->input)			/* If the line has any text in it, */
		add_history (mini->input);		/* save it on the history. */
	preparser(mini->input);
	free(mini->input);
}