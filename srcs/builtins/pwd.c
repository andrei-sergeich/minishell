#include "../include/minishell.h"

int	pwd_executing(void)
{
	char	*pwd;
//	int		i;

	pwd = ft_calloc(1024, sizeof(char));
//	i = -1;
//	while (++i < 2048)
//		pwd[i] = 0;
	if (getcwd(pwd, 1024))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		return (0);
	}
	else
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(pwd);
		return (1);
	}
}