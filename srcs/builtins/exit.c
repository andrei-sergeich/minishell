/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taredfor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:10:03 by taredfor          #+#    #+#             */
/*   Updated: 2022/01/28 23:58:52 by taredfor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	arrlen(char **arr)
{
	int	len;

	len = 0;
	if (arr == NULL)
		return (0);
	while (arr[len])
		len++;
	return (len);
}

int	isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	print_and_exit(t_shell *mini, char *argv1, char *str)
{
	ft_putstr_fd(BEGIN(49, 32)"minishell: "CLOSE, STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	if (argv1 != NULL)
	{
		ft_putstr_fd(argv1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (argv1 != NULL)
	{
		shlvl_down(mini);
		g_ext_stat = 255;
		exit(255);
	}
	else
		return (1);
}

static unsigned char	atoi_char(t_shell *mini, char *str)
{
	int				negative;
	int				i;
	long long int	convert;

	negative = 1;
	i = 0;
	convert = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		convert = convert * 10 + (str[i++] - '0');
		if (i > 20)
			print_and_exit(mini, str, "numeric argument required");
	}
	if ((convert - 3 >= 9223372036854775807 && negative == -1) \
			|| (convert - 1 >= 9223372036854775807 && negative == 1))
		print_and_exit(mini, str, "numeric argument required");
	return (convert * negative);
}

int	exit_executing(t_shell *mini, char **argv)
{
	int	len;

	len = arrlen(argv);
	if (len == 1)
	{
		shlvl_down(mini);
		exit(g_ext_stat);
//		exit(0);
	}
	if (isdigit_str(argv[1]))
		return (print_and_exit(mini, argv[1], "numeric argument required"));
	if (len > 2)
		return (print_and_exit(mini, NULL, "too many arguments"));
	if (len == 2)
	{
		g_ext_stat = atoi_char(mini, argv[1]);
		shlvl_down(mini);
		exit(g_ext_stat);
//		exit(0);
	}
	return (0);
}
