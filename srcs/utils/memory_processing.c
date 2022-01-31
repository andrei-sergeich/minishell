/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:15:53 by cmero             #+#    #+#             */
/*   Updated: 2022/01/31 19:15:54 by cmero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*allocator(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Could not malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	initializator(t_shell *mini)
{
	mini->input = NULL;
	mini->env_copy = NULL;
	mini->cmds = NULL;
	mini->args = NULL;
}

void	liberator(t_shell *mini)
{
	args_destroy(&mini->args);
	cmds_destroy(&mini->cmds);
}

void	array_liberator(char **array)
{
	int	it;

	it = 0;
	while (array[it])
	{
		free(array[it]);
		array[it] = NULL;
		it++;
	}
	free(array);
	array = NULL;
}
