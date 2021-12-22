#include "../include/minishell.h"

t_arg	*args_lstnew(char *arg_str, t_shell *mini)
{
	t_arg	*element;

	element = (t_arg *)malloc(sizeof(t_arg));
	if (!element)
		return (NULL);
	element->arg_as_is = ft_strdup(env_str);
	element->arg_cleaned = copy_key(env_str);
	if (ft_strcmp(element->key, "OLDPWD") == 0)
		element->value = NULL;
	else
		element->value = copy_value(env_str);
	element->next = NULL;
	free (arg_str);
	return (element);
}

int	find_end(char *input, int it, int *flag)
{
	char	quote;

	while (input[it])
	{
		if (input[it] == '\'' || input[it] == '\"')
		{
			quote = input[it];
			it++;
			while (input[it] && input[it] != quote)
				it++;
		}
		if (ft_strchr(" \t<|>", input[it]))
		{
			if (ft_strchr("<|>", input[it]))
				*flag = 1;
			if (ft_strchr("<>", input[it]) && ft_strchr("<>", input[it + 1]))
				*flag = 2;
//			it += ms_pass_whitespaces(&line[i]);
			return (it);
		}
		it++;
	}
	return (it);
}

void	split_input(char *input, t_arg **args, t_shell *mini)
{
	int	it;
	int	end;
	int	flag;

	it = 0;
	flag = 0;
	while (input[it])
	{
		it = pass_whitespaces(input, 0);
		if (input[it] == '\0')
			return ;
		end = find_end(input, it, &flag);
		if (flag != 0)
			return ;
		else
			args_lstadd_back(args, args_lstnew(ft_substr(input, 0, end), mini));
	}
}

t_arg	*arguments_processing(t_shell *mini)
{
	mini->args = NULL;
	split_input(mini->input, &(mini->args), mini);
	return (mini->args);
}
