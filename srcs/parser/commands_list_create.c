/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:07:23 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:07:24 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_full_command(t_argl *args)
{
	int		quantity;
	t_argl	*tmp;

	if (!args)
		return (0);
	tmp = args;
	quantity = 1;
	if (ft_strcmp("|", tmp->arg_origin) == 0)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (ft_strcmp(tmp->arg_origin, "|") == 0)
			return (quantity);
		quantity++;
	}
	return (quantity);
}

char	**write_cmd_to_array(t_argl *args, int quantity_lists)
{
	int		it;
	char	**arg_arr;

	it = 0;
	arg_arr = malloc(sizeof(char *) * (quantity_lists + 1));
	if (!arg_arr)
		return (NULL);
	while (args && (quantity_lists != 0))
	{
		arg_arr[it] = ft_strdup(args->arg_origin);
		it++;
		quantity_lists--;
		args = args->next;
	}
	arg_arr[it] = NULL;
	return (arg_arr);
}

t_cmdl	*cmds_lstnew(t_argl *args)
{
	t_cmdl	*element;
	int		quantity_lists;

	element = (t_cmdl *)malloc(sizeof(t_cmdl));
	if (!element || !args)
		return (NULL);
	element->redir = NULL;
	element->redir = (struct s_rdr *) redirect_processing(&args);
	quantity_lists = find_full_command(args);
	element->command = write_cmd_to_array(args, quantity_lists);
	element->in = 0;
	element->out = 1;
	element->fork = 0;
	element->pipe_fd[0] = 0;
	element->pipe_fd[1] = 0;
	element->next = NULL;
	return (element);
}

void	cmds_lstadd_back(t_cmdl	**list, t_cmdl *new)
{
	t_cmdl	*last;

	if (!list || !new)
		exit(EXIT_FAILURE);
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
