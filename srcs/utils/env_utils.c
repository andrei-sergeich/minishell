/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:15:19 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:15:28 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	envl_lstdelone(t_envl *lst)
{
	if (!lst)
		return ;
	free(lst->line);
	lst->line = NULL;
	free(lst->key);
	lst->key = NULL;
	free(lst->value);
	lst->value = NULL;
	free(lst);
	lst = NULL;
}

void	envl_destroy(t_envl **lst)
{
	t_envl	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		envl_lstdelone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	env_copy_lstsize(t_envl *env_copy)
{
	int		count;

	if (!env_copy)
		return (-1);
	count = 0;
	while (env_copy)
	{
		env_copy = env_copy->next;
		count++;
	}
	return (count);
}

char	*find_in_env(t_envl *env_copy, char *key)
{
	if (!env_copy || !key)
		return (NULL);
	while (env_copy)
	{
		if (!ft_strcmp(env_copy->key, key))
			return (env_copy->value);
		env_copy = env_copy->next;
	}
	return (NULL);
}

void	change_value_in_env_copy(t_envl *env_copy, char *key, char *value)
{
	if (!env_copy || !key || !value)
		return ;
	while (env_copy)
	{
		if (!ft_strcmp(env_copy->key, key))
		{
			if (env_copy->line)
				free(env_copy->line);
			env_copy->line = ft_strjoin_con(key, "=", value);
			if (env_copy->value)
				free(env_copy->value);
			env_copy->value = ft_strdup(value);
			return ;
		}
		env_copy = env_copy->next;
	}
}
