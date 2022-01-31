/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:12:05 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:12:06 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
