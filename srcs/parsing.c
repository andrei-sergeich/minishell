#include "../include/minishell.h"

char	*is_quote(char *str, int *it)
{
	int		begin;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	begin = *it;
	while (str[++(*it)])
	{
		if (str[*it] == '\'')
			break ;
	}
	tmp_1 = ft_substr(str, 0, begin);
	tmp_2 = ft_substr(str, begin + 1, *it - begin - 1);
	tmp_3 = ft_strdup(str + *it + 1);
	free(str);
	str = NULL;
	str = ft_strjoin_con(tmp_1, tmp_2, tmp_3);
	free(tmp_1);
	free(tmp_2);
	free(tmp_3);
	return (str);
}

char	*is_slash(char *str, int *it)
{
	char	*tmp_1;
	char	*tmp_2;

	tmp_1 = ft_substr(str, 0, *it);
	tmp_2 = ft_strdup(str + *it + 1);
	free(str);
	str = NULL;
	str = ft_strjoin(tmp_1, tmp_2);
	free(tmp_1);
	free(tmp_2);
	(*it)++;
	return (str);
}

char	*is_db_quote(char *str, int *it, t_envl *env_copy)
{
	int		begin;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	begin = *it;
	while (str[++(*it)])
	{
		/* в двойных кавычках отрабатывает \, если после него идет ", $ или \ */
		if (str[*it] == '\\' && (str[*it + 1] == '\"' \
				|| str[*it + 1] == '$' || str[*it + 1] == '\\'))
			str = is_slash(str, it);
		if (str[*it] == '$')
			str = dollar(str, it, env_copy);
		if (str[*it] == '\"')
			break ;
	}
	tmp_1 = ft_substr(str, 0, begin);
	tmp_2 = ft_substr(str, begin + 1, *it - begin - 1);
	tmp_3 = ft_strdup(str + *it + 1);
	free(str);
	str = NULL;
	str = ft_strjoin_con(tmp_1, tmp_2, tmp_3);
	free(tmp_1);
	free(tmp_2);
	free(tmp_3);
	return (str);
}

int	key_checker(char c)
{
	if (c == '_' || ft_isalnum(c)) // replace on ft_isalpha????????????
		return (1);
	return (0);
}

char	*dollar(char *str, int *it, t_envl *env_copy)
{
	int		begin;
	char	*tmp;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	begin = *it;
	while (str[++(*it)])
	{
		if (!key_checker(str[*it]))
			break ;
	}
	if (*it == begin + 1)
		return (str);
	tmp = ft_substr(str, begin + 1, *it - begin - 1);
	while (env_copy)
	{
		if (!ft_strcmp(tmp, env_copy->key))
			tmp_2 = ft_strdup(env_copy->value);
		env_copy = env_copy->next;
	}
	tmp_1 = ft_substr(str, 0, begin);
	printf("tmp_2 = %s\n", tmp_2);
//	tmp_2 = ft_strdup(env_copy->value);
	tmp_3 = ft_strdup(str + *it);
	free(str);
	str = NULL;
	str = ft_strjoin_con(tmp_1, tmp_2, tmp_3);
	free(tmp);
	free(tmp_1);
	free(tmp_2);
	free(tmp_3);
//	printf("key = %s\n", tmp);
	return (str);
}

char	*preparser(char *str, t_envl *env_copy) // "", '', \, $, ;, |, >, >>, <, 'пробел'
{
	int	it;

	it = 0;
	while (str[it])
	{
		if (str[it] == '\'')
			str = is_quote(str, &it);
		if (str[it] == '\\')
			str = is_slash(str, &it);
		if (str[it] == '\"')
			str = is_db_quote(str, &it, env_copy);
		if (str[it] == '$')
			str = dollar(str, &it, env_copy);
		it++;
	}
	printf("str = %s\n", str);
	return (str);
}

int	validator(char *str)
{
	int	it;

	it = 0;
	while (str[it])
	{
		if (str[it] == '$' && str[it + 1] == '?')
			it++;
		it++;
	}
	return (it);
}

void	parsing(t_shell *mini, t_envl *env_copy)
{
	(void)env_copy;
	mini->input = NULL;
//	mini->input = readline(BEGIN(49, 32)"[minishell ]$ "CLOSE);
	mini->input = ft_strdup("co$USER mma'n\\nn'dd000\\'00co\"mm\\\"\"an'dddd'a");
	printf("mini->input = %s\n\n", mini->input);
	if (!mini->input)
		exit(0);
//	if (*mini->input)					/* If the line has any text in it, */
//		add_history (mini->input);		/* save it on the history. */
//	preparser(mini->input);
	mini->input = preparser(mini->input, env_copy);
//	printf("%p\n", mini->input);
	free(mini->input);
}