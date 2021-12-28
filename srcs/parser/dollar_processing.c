#include "../include/minishell.h"

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
