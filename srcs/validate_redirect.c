#include "../include/minishell.h"

int	last_check(char *input, int *it)
{
	*it = pass_whitespaces(input, *it);
	if (input[*it] == '\0')
		return (print_msg(1, \
						"syntax error near unexpected token `newline'", 258));
	if (input[*it] == '|')
		return (print_msg(1, "syntax error near unexpected token `|'", 258));
	if (input[*it] == '>')
		return (print_msg(1, "syntax error near unexpected token `>'", 258));
	if (input[*it] == '<')
		return (print_msg(1, "syntax error near unexpected token `<'", 258));
	return (0);
}

int	read_redirect(char *input, int *it)
{
	(*it)++;
	if (input[*it] == '\0' || input[*it] == '>')
		return (print_msg(1, "syntax error near unexpected token `newline'", 258));
	if (input[*it] == '|')
		return (print_msg(1, "syntax error near unexpected token `|'", 258));
	if (input[*it] == '<')
	{
		return (last_check(input, it + 1));
//		*it = pass_whitespaces(input, *it + 1);
//		if (input[*it] == '\0')
//			return (print_msg(1, "syntax error near unexpected token `newline'"));
//		if (input[*it] == '|')
//			return (print_msg(1, "syntax error near unexpected token `|'"));
//		if (input[*it] == '>')
//			return (print_msg(1, "syntax error near unexpected token `>'"));
//		if (input[*it] == '<')
//			return (print_msg(1, "syntax error near unexpected token `<'"));
	}
	else
	{
		return (last_check(input, it));
//		*it = pass_whitespaces(input, *it);
//		if (input[*it] == '\0')
//			return (print_msg(1, "syntax error near unexpected token `newline'"));
//		if (input[*it] == '|')
//			return (print_msg(1, "syntax error near unexpected token `|'"));
//		if (input[*it] == '>')
//			return (print_msg(1, "syntax error near unexpected token `>'"));
//		if (input[*it] == '<')
//			return (print_msg(1, "syntax error near unexpected token `<'"));
	}
	return (0);
}

int	write_redirect(char *input, int *it)
{
	(*it)++;
	if (input[*it] == '\0' || input[*it] == '|')
		return (print_msg(1, "syntax error near unexpected token `newline'", 258));
	if (input[*it] == '<')
		return (print_msg(1, "syntax error near unexpected token `<'", 258));
	if (input[*it] == '>')
	{
		return (last_check(input, it + 1));
//		*it = pass_whitespaces(input, *it + 1);
//		if (input[*it] == '\0')
//			return (print_msg(1, "syntax error near unexpected token `newline'"));
//		if (input[*it] == '|')
//			return (print_msg(1, "syntax error near unexpected token `|'"));
//		if (input[*it] == '>')
//			return (print_msg(1, "syntax error near unexpected token `>'"));
//		if (input[*it] == '<')
//			return (print_msg(1, "syntax error near unexpected token `<'"));
	}
	else
	{
		return (last_check(input, it));
//		*it = pass_whitespaces(input, *it);
//		if (input[*it] == '\0')
//			return (print_msg(1, "syntax error near unexpected token `newline'"));
//		if (input[*it] == '|')
//			return (print_msg(1, "syntax error near unexpected token `|'"));
//		if (input[*it] == '>')
//			return (print_msg(1, "syntax error near unexpected token `>'"));
//		if (input[*it] == '<')
//			return (print_msg(1, "syntax error near unexpected token `<'"));
	}
	return (0);
}

int	counting_redirect(char *input, int *it, char redirect)
{
	if (redirect == '>' && write_redirect(input, it))
		return (1);
	if (redirect == '<' && read_redirect(input, it))
		return (1);
	return (0);
}
