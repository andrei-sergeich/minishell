#include "../include/minishell.h"

int	executable_path(char *line)
{
	int	it;

	it = 0;
	while (line[it] && !ft_isalnum(line[it]))
	{
		if (line[it] == '/')
			return (1);
		it++;
	}
	return (0);
}

char	**get_paths(t_shell *mini)
{
	char	*path_value;
	char	**paths;

	path_value = find_in_env(mini->env_copy, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	return (paths);
}

char	*path_processing(t_shell *mini, char *line)
{
	int		it;
	char	*path;
	char	**paths;

	it = 0;
	if (executable_path(line))
		return (line);
	paths = get_paths(mini);
	if (!paths)
		return (NULL);
	while (paths[it])
	{
		path = ft_strjoin_con(paths[it], "/", line);
		if (!access(path, F_OK | X_OK))
		{
			array_liberator(paths);
			return (path);
		}
		free(path);
		it++;
	}
	array_liberator(paths);
	return (NULL);
}