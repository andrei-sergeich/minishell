#include "../include/minishell.h"

int	pass_whitespaces(char *input, int it)
{
	while (input[it] && (ft_strchr("\t", input[it]) || ft_strchr(" ", input[it])))
		it++;
	return (it);
}

void	heredoc(t_cmdl *cmd, char *stop)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, stop, ft_strlen(stop) + 1))
			break ;
		ft_putendl_fd(line, cmd->out);
		free(line);
	}
	close(cmd->out);
	exit(0);
}

int	opener(char *path, char flag)
{
	int	fd;

	fd = -1;
	if (flag == 'I')
		fd = open(path, O_RDONLY);
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'A')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
//		print_msg(1, strerror(errno), 258);
		exit(errno);

//		g_ext_stat = 1;
//		perror("Error");
//		exit(g_ext_stat);
	}
	return (fd);
}

int	find_file_name(char *input, int *it)
{
	int		fd;
	int		begin;
	char	*file_name;

	printf("input = |%s|\n", input);
//	(*it)++;
	*it = pass_whitespaces(input, (*it) + 1);
	printf("it = %c	%d\n", input[*it], *it);
	begin = *it;
	while (input[*it] && /*ft_isprint(input[*it]) && */ input[*it] != ' ')
	{
//		printf("it = %c	%d\n", input[*it], *it);
		(*it)++;
	}
	file_name = ft_substr(input, begin, *it - begin);
	printf("file_name = |%s|\n", file_name);
	fd = opener(file_name, 'I');
	if (fd > 0)
	{
		printf("%d\n", fd);
		return (0);
	}
	return (1);
}