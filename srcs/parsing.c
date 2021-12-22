#include "../include/minishell.h"

char	*is_slash(char *input, int *it)
{
	char	*tmp_1;
	char	*tmp_2;

	tmp_1 = ft_substr(input, 0, *it);
	tmp_2 = ft_strdup(input + *it + 1);
	free(input);
	input = NULL;
	input = ft_strjoin(tmp_1, tmp_2);
	free(tmp_1);
	free(tmp_2);
	(*it)++;
	return (input);
}

char	*postparser(char *input, t_envl *env_copy) // "", '', \, $, ;, |, >, >>, <, 'пробел'
{
	int	it;

	it = 0;
	while (input[it])
	{
		if (input[it] == '\'')
			input = is_quote(input, &it);
		if (input[it] == '\\')
			input = is_slash(input, &it);
		if (input[it] == '\"')
			input = is_db_quote(input, &it, env_copy);
		if (input[it] == '$')
			input = is_dollar(input, &it, env_copy);
		it++;
	}
	printf("str = %s\n", input);
	return (input);
}

void	parsing(t_shell *mini, t_envl *env_copy)
{
	mini->input = NULL;
//	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
//	mini->input = ft_strdup("co'$USER' mma'n\\nn'dd000\\'00co\"mm\\\"\"an'dddd'aa'aaa");
	mini->input = ft_strdup("ls \"co'$USER' mma'n'aaa\"");
//	mini->input = ft_strdup("	'	'	ls	|	-la");
//	mini->input = ft_strdup("grep time <           test.txt ; grep time < test");
	printf("mini->input = %s\n\n", mini->input);
	if (!mini->input)
		exit(0);
//	if (*mini->input)					/* If the line has any text in it, */
//		add_history (mini->input);		/* save it on the history. */
//	preparser(mini->input);
//	mini->input = pass_whitespaces(mini->input);
	if (validator(mini->input) == 0)
	{
		mini->input = postparser(mini->input, env_copy);
//		mini->args = arguments_processing(mini);
	}
//	printf("%p\n", mini->input);
	free(mini->input);
}
