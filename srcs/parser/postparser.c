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
//	printf("str = %s\n", input);
	return (input);
}
