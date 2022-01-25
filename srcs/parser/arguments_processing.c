#include "../include/minishell.h"

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
//			it = pass_whitespaces(input, it);
			return (it);
		}
		it++;
	}
	return (it);
}

void	split_input(char *input, t_argl **args, t_shell *mini)
{
	int		it;
	int		begin;
	int		end;
	int		flag;
	char	*tmp;

	it = 0;
	flag = 0;
	while (input[it] != '\0')
	{
		it = pass_whitespaces(input, it);
		begin = it;
		if (input[it] == '\0')
			return ;
		end = find_end(input, it, &flag);
		it = end;
		it = pass_whitespaces(input, it); // строка 22 переставлена сюда, чтобы в аргумент не записывались пробелы
		if (flag != 0)
		{
//			many_cmds();
			tmp = ft_substr(input, begin, end - begin);
			if (ft_strcmp(tmp, "\0"))
				args_lstadd_back(args, args_lstnew(tmp, mini));
			else
				free(tmp);
			args_lstadd_back(args, \
			args_lstnew(ft_substr(input, end, flag), mini));
			it += flag;
			flag = 0;
		}
		else
			args_lstadd_back(args, \
			args_lstnew(ft_substr(input, begin, end - begin), mini));
	}
}

t_argl	*arguments_processing(t_shell *mini)
{
	split_input(mini->input, &(mini->args), mini);
	set_redirect(mini->args);
	return (mini->args);
}
