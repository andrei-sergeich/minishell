/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:12:31 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:17:41 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (input[*it] == ';')
		return (print_msg(1, "syntax error near unexpected token `;'", 258));
	return (0);
}

int	read_redirect(char *input, int *it)
{
	(*it)++;
	if (input[*it] == '\0' || input[*it] == '>')
		return (print_msg(1, "syntax error near unexpected token `newline'", \
		258));
	if (input[*it] == '|')
		return (print_msg(1, "syntax error near unexpected token `|'", 258));
	if (input[*it] == '<')
	{
		(*it)++;
		return (last_check(input, it));
	}
	else
		return (last_check(input, it));
}

int	write_redirect(char *input, int *it)
{
	(*it)++;
	if (input[*it] == '\0' || input[*it] == '|')
		return (print_msg(1, "syntax error near unexpected token `newline'", \
		258));
	if (input[*it] == '<')
		return (print_msg(1, "syntax error near unexpected token `<'", 258));
	if (input[*it] == '>')
	{
		(*it)++;
		return (last_check(input, it));
	}
	else
		return (last_check(input, it));
}

int	counting_redirect(char *input, int *it, char redirect)
{
	if (redirect == '>' && write_redirect(input, it))
		return (1);
	if (redirect == '<' && read_redirect(input, it))
		return (1);
	(*it)--;			//?????????????????? ???? ???????????? ls >'1'
	return (0);
}
