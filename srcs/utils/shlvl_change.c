/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:16:28 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:16:29 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_down(t_shell *mini)
{
	char	*cur_lvl;
	char	*up_lvl;

	cur_lvl = find_in_env(mini->env_copy, "SHLVL");
	up_lvl = ft_itoa(ft_atoi(cur_lvl) - 1);
	change_value_in_env_copy(mini->env_copy, "SHLVL", up_lvl);
	free(up_lvl);
}

void	shlvl_up(t_shell *mini)
{
	char	*cur_lvl;
	char	*up_lvl;

	cur_lvl = find_in_env(mini->env_copy, "SHLVL");
	up_lvl = ft_itoa(ft_atoi(cur_lvl) + 1);
	change_value_in_env_copy(mini->env_copy, "SHLVL", up_lvl);
	free(up_lvl);
}
