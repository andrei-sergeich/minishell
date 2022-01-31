/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taredfor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 22:43:40 by taredfor          #+#    #+#             */
/*   Updated: 2022/01/28 23:05:52 by taredfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	old_pwd(t_shell *mini)
{
	char	*value;

	value = find_in_env(mini->env_copy, "OLDPWD");
	if (!value)
	{
		ft_putstr_fd(BEGIN(49, 32)"minishell: "CLOSE, STDERR_FILENO);
		ft_putendl_fd("cd : OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	else
	{
		ft_putendl_fd(value, 1);
		return (change_dir(mini, value));
	}
}

int	new_pwd(t_shell *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	else
	{
		if (mini->env_copy == NULL)
			return (1);
		change_value_in_env_copy(mini->env_copy, "PWD", pwd);
		free(pwd);
		return (0);
	}
}
