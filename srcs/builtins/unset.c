/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taredfor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 00:01:05 by taredfor          #+#    #+#             */
/*   Updated: 2022/01/29 00:03:24 by taredfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//static void	free_lst(t_envl	*lst)
//{
//	free(lst->value);
//	free(lst->key);
//	free(lst->line);
//	free(lst);
//}

static void	del_elem(t_envl **head)
{
	t_envl	*for_del;

	for_del = (*head)->next;
	(*head)->next = (*head)->next->next;
//	free_lst(for_del);
	envl_lstdelone(for_del);
}

static void	del_nth(t_envl **head, int n)
{
	t_envl	*prev;
	t_envl	*cur;

	prev = NULL;
	cur = NULL;
	if (!(*head) || !head)
		return ;
	if (n == 0)
	{
		prev = (*head);
		(*head) = (*head)->next;
//		free_lst(prev);
		envl_lstdelone(prev);
	}
	else if (n >= 0)
	{
		cur = (*head);
		while (--n)
			cur = cur->next;
		del_elem(&(cur));
	}
}

int	find_in_env_ind(t_envl *lst, char *key)
{
	int		index;
	t_envl	*tmp;

	index = 0;
	tmp = lst;
	if (tmp && key)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, key))
				return (index);
			index++;
			tmp = tmp->next;
		}
	}
	return (-1);
}

int	unset_executing(t_shell *mini, char **argv)
{
	int	ind_del;
	int	i;

	i = 1;
	if (arrlen(argv) == 1)
		return (0);
	else
	{
		while (argv[i])
		{
			ind_del = find_in_env_ind(mini->env_copy, argv[i]);
			if (ind_del >= 0)
				del_nth(&(mini->env_copy), ind_del);
			ind_del = -1;
			i++;
		}
	}
	return (0);
}
