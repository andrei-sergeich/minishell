#include "../include/minishell.h"

int	pass_whitespaces(char *input, int it)
{
	while (input[it] && (ft_strchr("\t", input[it]) || ft_strchr(" ", input[it])))
		it++;
	return (it);
}

void	execute_heredoc(t_cmdl *cmd, char *stop)
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

void	heredoc_processing(t_cmdl *cmd)
{
	int	fd[2];
	int	pid;
	t_redir	*tmp;

	tmp = (t_redir *) cmd->redir;
	if (ft_strcmp("<<", tmp->type) != 0)
	{
		write(1, "tut", 3);
		write(1, "\n", 1);
		return ;
	}
	if (pipe(fd) < 0)
	{
		perror("Error");
//		g_ext_stat = 1;
//		exit (g_ext_stat);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		cmd->out = fd[1];
		execute_heredoc(cmd, tmp->name);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		cmd->in = fd[0];
	}
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

void	fd_opening(t_cmdl *cmds)
{
	t_redir	*tmp;
	int		it;

	if (cmds == NULL)
		return ;
//	while (cmds)
//	{
		it = 0;
		tmp = (t_redir *) cmds->redir;
		while (tmp)
		{
//			printf("%d * redirect type - |%s| \t name - |%s|\n", it, tmp->type, tmp->name);
			if (ft_strcmp("<", tmp->type) == 0)
				cmds->in = opener(tmp->name, 'I');
			if (ft_strcmp(">", tmp->type) == 0)
				cmds->out = opener(tmp->name, 'O');
			if (ft_strcmp(">>", tmp->type) == 0)
				cmds->out = opener(tmp->name, 'A');
			tmp = tmp->next;
			it++;
		}
//		printf("in - |%d| \t out - |%d|\n", cmds->in, cmds->out);
//		cmds = cmds->next;
//	}
}
