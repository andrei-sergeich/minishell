/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taredfor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 00:04:29 by taredfor          #+#    #+#             */
/*   Updated: 2022/01/28 23:08:01 by taredfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *ft_find_home(t_envl **lst)
{
	t_envl	*tmp;
	char 	*cp_value;

	cp_value = NULL;
	if (lst && (*lst))
	{
		tmp = *lst;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, "HOME"))
			{
				cp_value = ft_strdup(tmp->value);
				return (cp_value);
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}

static int ft_not_set(void)
{
	ft_putstr_fd(BEGIN(49, 32)"minishell: "CLOSE, STDERR_FILENO);
	ft_putendl_fd("cd :  HOME not set", STDERR_FILENO);
	return (1);
}

int	change_dir(t_shell *mini, char *path)
{
	char *oldpwd;

	oldpwd = getcwd(NULL, 1024);
	if (!oldpwd)
		oldpwd = ft_strdup(find_in_env(mini->env_copy, "HOME"));
	change_value_in_env_copy(mini->env_copy,"OLDPWD", oldpwd);
	if (chdir(path))
	{
		ft_putstr_fd(BEGIN(49, 32)"minishell: "CLOSE, STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(oldpwd);
		return (1);
	}
	else
	{
		free(oldpwd);
		return (new_pwd(mini));
	}
}

int	change_way(t_shell *mini, char **argv)
{
	char *cd[2];

	if (argv[1][0] == '-')
		return (old_pwd(mini));
	else if ((argv[1][0]) == '~')
	{
		cd[0] = "cd";
		cd[1] = NULL;
		return (cd_executing(mini, cd));
	}
	return (change_dir(mini, argv[1]));
}

int	cd_executing(t_shell *mini, char **argv)
{
	char *home;
	int 	res;

	home = NULL;
	if (arrlen(argv) > 1)
		return (change_way(mini, argv));
	else
	{
		home = ft_find_home(&mini->env_copy);
		if (!home)
			return (ft_not_set());
		res = change_dir(mini, home);
		free(home);
		return (res);
	}
}