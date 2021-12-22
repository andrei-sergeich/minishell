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
//			i += ms_pass_whitespaces(&line[i]);
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

	(void)args;
	(void)mini;
	it = 0;
	flag = 0;
	while (input[it])
	{
		it = pass_whitespaces(input, 0);
		if (input[it] == '\0')
			return ;
		end = find_end(input, it, &flag);
	}
}

t_arg	*arguments_processing(t_shell *mini)
{
	mini->args = NULL;
	split_input(mini->input, &(mini->args), mini);
	return (mini->args);
}
