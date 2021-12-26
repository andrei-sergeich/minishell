#include "../include/minishell.h"

t_arg	*args_lstnew(char *arg_str, t_shell *mini)
{
	t_arg	*element;

	element = (t_arg *)malloc(sizeof(t_arg));
	if (!element)
		return (NULL);
//	element->arg_as_is = ft_strdup(arg_str);
	element->arg_cleaned = postparser(arg_str, mini->env_copy);
	element->redirect = 0;
	element->next = NULL;
//	free (arg_str);
	return (element);
}

void	args_lstadd_back(t_arg	**list, t_arg *new)
{
	t_arg	*last;

	if (!list || !new)
		exit(EXIT_FAILURE); 			/* or return */
	if (*list)
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*list = new;
}

int	find_end(char *input, int it, int *flag)
{
	char	quote;

//	it--;
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
			it = pass_whitespaces(input, it);
			return (it);
		}
		it++;
	}
	return (it);
}

void	split_input(char *input, t_arg **args, t_shell *mini)
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
		if (flag != 0)
		{
			tmp = ft_substr(input, begin, end - begin);
			if (ft_strcmp(tmp, "\0"))
				args_lstadd_back(args, args_lstnew(tmp, mini));
			else
				free(tmp);
			args_lstadd_back(args, args_lstnew(ft_substr(input, end, flag), mini));
			it += flag;
			flag = 0;
//			return;
		}
		else
			args_lstadd_back(args, \
			args_lstnew(ft_substr(input, begin, end - begin), mini));
//		it++;
	}
}

t_arg	*arguments_processing(t_shell *mini)
{
	mini->args = NULL;
	split_input(mini->input, &(mini->args), mini);
	print_args(mini);
	return (mini->args);
}
