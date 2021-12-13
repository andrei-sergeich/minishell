#include "../include/minishell.h"

int	pass_whitespaces(char *input, int it)
{
//	int	it;
//
//	it = 0;
	while (ft_strchr("\t", input[it]) || ft_strchr(" ", input[it]))
		it++;
	return (it);
}

int	counting_pipes_or_delimeters(char *input, int it)
{
//	g_ext_stat = 258;
	if (input[it] == '|' && input[it + 1] == '|')
		return (print_msg(1, "syntax error near unexpected token `||'"));
	else if (input[it] == '|')
		return (print_msg(1, "syntax error near unexpected token `|'"));
	else if (input[it] == ';' && input[it + 1] == ';')
		return (print_msg(1, "syntax error near unexpected token `;;'"));
	else if (input[it] == ';')
		return (print_msg(1, "syntax error near unexpected token `;'"));
	return (0);
}

int	counting_quotes(char *input, int *it, char quote)
{
	while (input[++(*it)])
	{
		if (input[*it] == quote)
		{
			(*it)++;
			return (0);
		}
	}
//	g_ext_stat = 258;
	return (print_msg(1, "syntax error with unclosed quotes"));
}

int	validator(char *input)
{
	int	it;

	if (!input)
		return (1);
	it = pass_whitespaces(input, 0);
	if (input[it] == '|' || input[it] == ';')
		return (counting_pipes_or_delimeters(input, it));
	while (input[it])
	{
		if (input[it] == '\'' && counting_quotes(input, &it, input[it]))
			return (1);
//		printf("%c\t%d\n", input[it], it);
		if (input[it] == '\"' && counting_quotes(input, &it, input[it]))
			return (1);
//		if ((input[it] == '<' || input[it] == '>') && counting_quotes(input, &it, input[it]))
//			return (1);
		if (input[it] == '<' && find_file_name(input, &it))
//			printf("it = %d\n", it);
			return (1);
		it++;
	}
	return (0);
}
