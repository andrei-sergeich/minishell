#include "../include/minishell.h"

void	execute_heredoc(t_cmdl *cmd, char *stop)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(input, stop, ft_strlen(stop) + 1))
			break ;
		ft_putendl_fd(input, cmd->out);
		free(input);
	}
	close(cmd->out);
	exit(0);
}

void	heredoc_processing(t_cmdl *cmd)
{
	int		fd[2];
	int		pid;
	t_redir	*tmp;

	tmp = (t_redir *) cmd->redir;
	while (tmp)
	{
		if (pipe(fd) < 0)
		{
			perror("Error");
			g_ext_stat = 1;
			exit (g_ext_stat);
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
		tmp = tmp->next;
	}
}

int	heredoc_checking(t_cmdl *cmd)
{
	t_redir	*tmp;

	if (!cmd->redir)
		return (0);
	tmp = (t_redir *) cmd->redir;
	if (ft_strcmp("<<", tmp->type) == 0)
	{
//		write(1, "tut", 3);
//		write(1, "\n", 1);
		return (1);
	}
	return (0);
}
