/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taredfor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 00:05:52 by taredfor          #+#    #+#             */
/*   Updated: 2022/01/29 00:08:14 by taredfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	swap_action(t_envl **lst)
{
	t_envl	*tmp;

	if ((*lst) || (*lst)->next || (*lst)->next->next)
	{
		tmp = (*lst)->next;
		(*lst)->next = (*lst)->next->next;
		tmp->next = (*lst);
		(*lst) = tmp;
	}
}

static int	sorting(t_envl **lst)
{
	int		flag;
	t_envl	*cur;

	flag = 0;
	if (!(*lst) || !(*lst)->next)
		return (0);
	if (ft_strcmp((*lst)->key, (*lst)->next->key) > 0)
		swap_action(lst);
	cur = (*lst);
	while (cur->next->next)
	{
		if (ft_strcmp(cur->next->key, cur->next->next->key) > 0)
		{
			swap_action(&(cur->next));
			flag++;
		}
		cur = cur->next;
	}
	if (flag)
		sorting(lst);
	return (0);
}

int	not_valid(char *agr)
{
	ft_putstr_fd (BEGIN(49, 32)"minishell: "CLOSE, STDERR_FILENO);
	ft_putstr_fd("export`", STDERR_FILENO);
	ft_putstr_fd(agr, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

static int	check_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
		return (not_valid(arg));
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
			return (not_valid(arg));
		if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]))
			return (not_valid(arg));
		i++;
	}
	return (0);
}

int	export_executing(t_shell *mini, char **argv)
{
	char	*key;
	char	*value;

	if (arrlen(argv) == 1)
		return (sorting(&mini->env_copy) + print_env_l(mini->env_copy));
	else
	{
		while (*++argv)
		{
			if (check_export(*argv))
				return (1);
			key = copy_key(*argv);
			value = copy_value(*argv);
			if (is_key_exist(&mini->env_copy, key))
				change_value_in_env_copy(mini->env_copy, key, value);
			else
				envl_lstadd_back(&mini->env_copy, envl_lstnew(*argv));
			free(key);
			if (value)
				free(value);
		}
	}
	return (0);
}