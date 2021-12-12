#include "../include/minishell.h"

char	*str_handler(char *input, int begin, int end)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	tmp_1 = ft_substr(input, 0, begin);
	tmp_2 = ft_substr(input, begin + 1, end - begin - 1);
	tmp_3 = ft_strdup(input + end + 1);
	free(input);
	input = NULL;
	input = ft_strjoin_con(tmp_1, tmp_2, tmp_3);
	free(tmp_1);
	free(tmp_2);
	free(tmp_3);
	return (input);
}

char	*is_quote(char *input, int *it)
{
	int		begin;

	begin = *it;
	while (input[++(*it)])
	{
		if (input[*it] == '\'')
			break ;
	}
	input = str_handler(input, begin, *it);
	return (input);
}

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

char	*is_db_quote(char *input, int *it, t_envl *env_copy)
{
	int		begin;

	begin = *it;
	while (input[++(*it)])
	{
		/* в двойных кавычках отрабатывает \, если после него идет ", $ или \ */
		if (input[*it] == '\\' && (input[*it + 1] == '\"' \
				|| input[*it + 1] == '$' || input[*it + 1] == '\\'))
			input = is_slash(input, it);
		if (input[*it] == '$')
			input = is_dollar(input, it, env_copy);
		if (input[*it] == '\"')
			break ;
	}
	input = str_handler(input, begin, *it);
	return (input);
}

int	key_checker(char c)
{
	if (c == '_' || ft_isalnum(c)) // replace on ft_isalpha????????????
		return (1);
	return (0);
}

char	*key_handler(char *input, int begin, int end, t_envl *env_copy)
{
	char	*key;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	key = ft_substr(input, begin + 1, end - begin - 1);
	tmp_1 = ft_substr(input, 0, begin);
	tmp_3 = ft_strdup(input + end);
	tmp_2 = ft_strdup(find_in_env(env_copy, key));
	free(input);
	input = NULL;
	if (tmp_2 == NULL)
		input = ft_strjoin(tmp_1, tmp_3);
	else
		input = ft_strjoin_con(tmp_1, tmp_2, tmp_3);
	free(key);
	free(tmp_1);
	free(tmp_2);
	free(tmp_3);
	return (input);
}

char	*is_dollar(char *input, int *it, t_envl *env_copy)
{
	int		begin;

	begin = *it;
	while (input[++(*it)])
	{
		if (!key_checker(input[*it]))
			break ;
	}
	if (*it == begin + 1)
		return (input);
	input = key_handler(input, begin, *it, env_copy);
	return (input);
}

char	*preparser(char *input, t_envl *env_copy) // "", '', \, $, ;, |, >, >>, <, 'пробел'
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
	(void)env_copy;
	mini->input = NULL;
	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
//	mini->input = ft_strdup("co$USERR mma'n\\nn'dd000\\'00co\"mm\\\"\"an'dddd'a");
//	mini->input = ft_strdup("	'	'	ls	|	-la");
	printf("mini->input = %s\n\n", mini->input);
	if (!mini->input)
		exit(0);
//	if (*mini->input)					/* If the line has any text in it, */
//		add_history (mini->input);		/* save it on the history. */
//	preparser(mini->input);
//	mini->input = pass_whitespaces(mini->input);
	if (validator(mini->input) == 0)
		mini->input = preparser(mini->input, env_copy);
//	printf("%p\n", mini->input);
	free(mini->input);
}
