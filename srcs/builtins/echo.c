#include "../include/minishell.h"

int	echo_executing(char **arr)
{
	int flag;
	int i;

	flag = 1;
	i = 1;
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], "-n"))
		{
			flag = 0;
			i++;
			continue;
		}
		ft_putstr_fd(arr[i], STDOUT_FILENO);
		i++;
		if (arr[i] == NULL)
			break;
		else
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (flag == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}